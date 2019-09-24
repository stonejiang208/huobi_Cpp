#include "WebSocketConnection.h"
#include "Utils/ApiSignature.h"
#include "Utils/JsonDocument.h"
#include "Utils/JsonWriter.h"
#include "GetHost.h"
#include "TimeService.h"
#include "Huobi/SubscriptionOptions.h"
#include <ctime>
#include <stdbool.h>

namespace Huobi {

    void fail(beast::error_code ec, char const* what) {
        std::cerr << what << ": " << ec.message() << "\n";
    }

    int WebSocketConnection::connectionCounter = 0;

    WebSocketConnection::WebSocketConnection(
            WebSocketRequest* request,
            const std::string& apiKey, const std::string& secretKey,
            const SubscriptionOptionsHandler& op,
            boost::asio::io_context& io, boost::asio::ssl::context& ssl)
    : apiKey_(apiKey), secretKey_(secretKey)
    , request(request)
    , resolver_(asio::make_strand(io))
    , ws_(asio::make_strand(io), ssl) {
        host = GetHost(op->url);
        this->connectionId = connectionCounter++;
        lineStatus_ = LineStatus::LINE_IDEL;
        if (host.find("api") == 0) {
            this->subscriptionMarketUrl = "wss://";
            this->subscriptionMarketUrl = this->subscriptionMarketUrl + host + "/ws";
            this->subscriptionTradingUrl = "wss://";
            this->subscriptionTradingUrl = this->subscriptionTradingUrl + host + "/ws/v1";
        } else {
            this->subscriptionMarketUrl = "wss://";
            this->subscriptionMarketUrl = this->subscriptionMarketUrl + host + "/api/ws";
            this->subscriptionTradingUrl = "wss://";
            this->subscriptionTradingUrl = this->subscriptionTradingUrl + host + "/ws/v1";
        }
    };

    void WebSocketConnection::on_resolve(beast::error_code ec, net::tcp::resolver::results_type results) {
        if (ec)
            return Logger::LogInfo("[Sub][%d] Failed to resolve host: ", connectionId, host.c_str());
        Logger::LogInfo("[Sub][%d] Resolved host", connectionId);
        // Set the timeout for the operation
        beast::get_lowest_layer(ws_).expires_after(std::chrono::seconds(30));

        // Make the connection on the IP address we get from a lookup
        beast::get_lowest_layer(ws_).async_connect(
                results,
                beast::bind_front_handler(
                &WebSocketConnection::on_connect,
                shared_from_this()));
    }

    void WebSocketConnection::on_connect(beast::error_code ec, net::tcp::resolver::results_type::endpoint_type) {
        if (ec)
            return fail(ec, "connect");
        Logger::LogInfo("[Sub][%d] Connected to host", connectionId);

        // Turn off the timeout on the tcp_stream, because
        // the websocket stream has its own timeout system.
        beast::get_lowest_layer(ws_).expires_never();

        // Set suggested timeout settings for the websocket
        ws_.set_option(
                beast::websocket::stream_base::timeout::suggested(
                beast::role_type::client));

        // Perform the websocket handshake
        // Perform the SSL handshake
        ws_.next_layer().async_handshake(
                asio::ssl::stream_base::client,
                beast::bind_front_handler(
                &WebSocketConnection::on_ssl_handshake,
                shared_from_this()));
    }

    void WebSocketConnection::on_ssl_handshake(beast::error_code ec) {
        if (ec)
            return fail(ec, "ssl_handshake");

        // Turn off the timeout on the tcp_stream, because
        // the websocket stream has its own timeout system.
        beast::get_lowest_layer(ws_).expires_never();

        // Set suggested timeout settings for the websocket
        //        ws_.set_option(
        //            websocket::stream_base::timeout::suggested(
        //                beast::role_type::client));

        // Set a decorator to change the User-Agent of the handshake
        //        ws_.set_option(websocket::stream_base::decorator(
        //            [](websocket::request_type& req)
        //            {
        //                req.set(http::field::user_agent,
        //                    std::string(BOOST_BEAST_VERSION_STRING) +
        //                        " websocket-client-async-ssl");
        //            }));

        // Perform the websocket handshake
        std::string path;
        if (request->isNeedSignature == true) {
            path = "/ws/v1";
        } else {
            if (host.find("api") != -1) {
                path = "/ws";
            } else {
                path = "/api/ws";
            }
        }
        Logger::LogInfo("[Sub][%d] Connected to %s", connectionId, path.c_str());
        ws_.async_handshake(host, path,
                beast::bind_front_handler(
                &WebSocketConnection::on_handshake,
                shared_from_this()));
    }

    void WebSocketConnection::on_handshake(beast::error_code ec) {
        if (ec)
            return fail(ec, "handshake");
        lineStatus_ = LINE_CONNECTED;
        lastReceivedTime_ = TimeService::getCurrentTimeStamp();
        ws_.async_read(
                buffer_,
                beast::bind_front_handler(
                &WebSocketConnection::on_read,
                shared_from_this()));

        if (request->isNeedSignature) {
            send(createSignature());
        } else {
            if (request->connectionHandler) {
                request->connectionHandler(this);
            }
        }
    }

    void WebSocketConnection::connect() {
        if (lineStatus_ == LINESTATUS::LINE_CONNECTED) {
            Logger::LogWarning("[Sub][%d] Already connect", connectionId);
            return;
        }
        lineStatus_ = LINE_CONNECTING;
        Logger::LogInfo("[Sub][%d] Connecting to host: %s", connectionId, host.c_str());
        // Look up the domain name
        resolver_.async_resolve(
                host,
                "443",
                beast::bind_front_handler(
                &WebSocketConnection::on_resolve,
                shared_from_this()));
    }

    void WebSocketConnection::on_read(beast::error_code ec, std::size_t bytes_transferred) {
        boost::ignore_unused(bytes_transferred);
        if (ec) {
            std::cout << "---- on_read ERROR" << std::endl;
            return fail(ec, "read");
        }
        char buf[4096 * 4] = {0};
        unsigned int l = 4096 * 4;
        l = gzDecompress((char*) buffer_.data().data(), buffer_.size(), buf, l);
        //lwsl_user("RX %d: %s\n", l, (const char *) buf);
        Logger::LogInfo("RX: %s", (const char *) buf);
        onMessage(buf);
        buffer_.clear();

        ws_.async_read(
                buffer_,
                beast::bind_front_handler(
                &WebSocketConnection::on_read,
                shared_from_this()));
    }

    void WebSocketConnection::on_write(
            beast::error_code ec,
            std::size_t bytes_transferred) {
        boost::ignore_unused(bytes_transferred);

        if (ec)
            return fail(ec, "write");
    }

    void WebSocketConnection::send(const std::string& message) {
        Logger::LogDebug("Send: %s", message.c_str());
        ws_.async_write(asio::buffer(message),
                beast::bind_front_handler(
                &WebSocketConnection::on_write,
                shared_from_this()));
    }

    void WebSocketConnection::onMessage(const char* message) {
        lastReceivedTime_ = TimeService::getCurrentTimeStamp();

        JsonDocument doc;
        JsonWrapper json = doc.parseFromString(message);
        if ((json.containKey("status") && strcmp(json.getString("status"), "ok") != 0) ||
                (json.containKey("err-code") && json.getInt("err-code") != 0)) {
            std::string errorCode = json.getStringOrDefault("err-code", "Unknown error code");
            std::string errorMsg = json.getStringOrDefault("err-msg", "Unknown error message");
            HuobiApiException ex;
            ex.errorCode = errorCode;
            ex.errorMsg = errorMsg;
            request->errorHandler(ex);
            Logger::LogCritical("[Sub][%d] Error: %s", errorMsg.c_str());
            close();
        } else if (json.containKey("op")) {
            std::string op = json.getString("op");
            if (op == "notify") {
                onReceive(json);
            } else if (op == "ping") {
                processPingOnTradingLine(json);
            } else if (op == "auth") {
                if (request->connectionHandler) {
                    request->connectionHandler(this);
                }
            }
        } else if (json.containKey("ch")) {
            onReceive(json);
        } else if (json.containKey("ping")) {
            processPingOnMarketLine(json);
        } else if (json.containKey("subbed")) {

        } else {
            Logger::LogCritical("parse failed！：%s", message);
        }
    }

    void WebSocketConnection::onReceive(JsonWrapper& json) {
        request->implCallback(json);
    }

    void WebSocketConnection::processPingOnTradingLine(JsonWrapper& json) {
        long ts = json.getLong("ts");
        char buf[1024] = {0};
        sprintf(buf, "{\"op\":\"pong\",\"ts\":%ld}", ts);
        std::string message = buf;
        send(message);
    }

    void WebSocketConnection::processPingOnMarketLine(JsonWrapper& json) {
        long ts = json.getLong("ping");
        char buf[1024] = {0};
        sprintf(buf, "{\"pong\":%ld}", ts);
        std::string message = buf;
        send(message);
    }

    std::string WebSocketConnection::createSignature() {

        time_t t = time(NULL);
        struct tm *local = gmtime(&t);
        char timeBuf[100] = {0};
        sprintf(timeBuf, "%04d-%02d-%02dT%02d%%3A%02d%%3A%02d",
                local->tm_year + 1900,
                local->tm_mon + 1,
                local->tm_mday,
                local->tm_hour,
                local->tm_min,
                local->tm_sec);
        char buf[100] = {0};
        sprintf(buf, "%04d-%02d-%02dT%02d:%02d:%02d",
                local->tm_year + 1900,
                local->tm_mon + 1,
                local->tm_mday,
                local->tm_hour,
                local->tm_min,
                local->tm_sec);
        std::string signa = ApiSignature::CreateSignature(host,
                apiKey_,
                secretKey_,
                "/ws/v1", "GET", timeBuf, "");

        JsonWriter writer;
        writer.put("SignatureVersion", "2");
        writer.put("op", "auth");
        writer.put("AccessKeyId", apiKey_);
        writer.put("Signature", signa.c_str());
        writer.put("SignatureMethod", "HmacSHA256");
        writer.put("Timestamp", buf);
        return writer.toJsonString();
    }

    long WebSocketConnection::getLastReceivedTime() {

        return lastReceivedTime_;
    }

    void WebSocketConnection::reConnect() {
        if (delayInSecond != 0) {
            delayInSecond--;
        } else {
            this->connect();
        }
    }

    void WebSocketConnection::reConnect(int delayInSecond) {
        Logger::LogWarning("[Sub][%d] Reconnecting after %d seconds later", connectionId, delayInSecond);
        if (ws_.is_open()) {
            //lwsl_user("closing client\n");
            close();
        } else {
            //lwsl_user("client is null\n");
        }
        this->delayInSecond = delayInSecond;
        lineStatus_ = LineStatus::LINE_DELAY;
    }

    void WebSocketConnection::disconnect() {
        Logger::LogInfo("[Sub][%d] Disconnected", connectionId);
    }

    void WebSocketConnection::close() {
        Logger::LogInfo("[Sub][%d] Closing normally", connectionId);
        lineStatus_ = LineStatus::LINE_DISCONNECTING;
        ws_.close(beast::websocket::close_code::normal);
        lineStatus_ = LineStatus::LINE_IDEL;
    }

    //    void WebSocketConnection::closeOnError() {
    //        Logger::LogInfo("[Sub][%d] Closing normally", connectionId);
    //        lineStatus_ = LineStatus::LINE_DISCONNECTING;
    //        ws_.close(beast::websocket::close_code::normal);
    //        lineStatus_ = LineStatus::LINE_IDEL;
    //    }
}


