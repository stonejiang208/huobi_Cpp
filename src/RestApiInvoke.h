#ifndef RESTAPIINVOKE_H
#define RESTAPIINVOKE_H
#include <memory>
#include "RestApi.h"
#include "Utils/JsonDocument.h"
#include "EtfResult.h"
#include "Huobi/HuobiApiException.h"
#include "Huobi/Logger.h"
#include "Utils/Singleton.h"

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/error.hpp>
#include <boost/asio/ssl/stream.hpp>



namespace Huobi {

    class RestApiInvoke : public Singleton<RestApiInvoke> {
    private:
        boost::asio::ssl::context ctx_;
        // The io_context is required for all I/O
        boost::asio::io_context ioc_;
        boost::asio::ip::tcp::resolver resolver_;
    protected:
        friend class Singleton<RestApiInvoke>;

        RestApiInvoke()
        : ctx_(boost::asio::ssl::context::sslv23_client)
        , resolver_(ioc_) {
            ctx_.set_verify_mode(boost::asio::ssl::verify_peer);
            ctx_.load_verify_file("/etc/huobi_cert/cert.pem");
        }

    private:

        template <typename T>
        T callSync_Boost(RestApi<T>* request) {
            static boost::beast::flat_buffer buffer;
            std::unique_ptr<RestApi < T >> ptr(request);

            boost::beast::ssl_stream<boost::beast::tcp_stream> stream(ioc_, ctx_);

            // Set SNI Hostname (many hosts need this to handshake successfully)
            if (!SSL_set_tlsext_host_name(stream.native_handle(), ptr->host.c_str())) {
                boost::beast::error_code ec{static_cast<int> (::ERR_get_error()), boost::asio::error::get_ssl_category()};
                throw boost::beast::system_error{ec};
            }
            auto const results = resolver_.resolve(ptr->host.c_str(), "443");

            Logger::LogDebug("[RESTfulSync] Connecting host: %s", ptr->host.c_str());
            boost::beast::get_lowest_layer(stream).expires_after(std::chrono::seconds(20));
            boost::beast::get_lowest_layer(stream).connect(results);
            
            stream.handshake(boost::asio::ssl::stream_base::client);

            if (ptr->method == "POST") {
                boost::beast::http::request<boost::beast::http::string_body> req{boost::beast::http::verb::post, ptr->path.c_str(), 11};
                req.set(boost::beast::http::field::host, ptr->host.c_str());
                req.set(boost::beast::http::field::content_type, "application/json;charset=UTF-8");
                req.body() = ptr->postbody;
                req.prepare_payload();
                boost::beast::http::write(stream, req);
            } else {
                boost::beast::http::request<boost::beast::http::string_body> req{boost::beast::http::verb::get, ptr->path.c_str(), 11};
                req.set(boost::beast::http::field::host, ptr->host.c_str());
                req.set(boost::beast::http::field::content_type, "application/x-www-form-urlencoded");
                boost::beast::http::write(stream, req);
            }
            std::cout << "-- Send request Done" << std::endl;
            boost::beast::http::response<boost::beast::http::string_body> res;
            buffer.clear();
            // Receive the HTTP response
            boost::beast::http::read(stream, buffer, res);
            std::cout << "-- Get response" << std::endl;
            // Write the message to standard out
            std::cout << res.body().c_str() << std::endl;

            try {
                stream.shutdown();
            } catch (std::exception const& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }

            JsonDocument djson;
            JsonWrapper json = djson.parseFromString(res.body().c_str());
            RestApiInvoke::checkResponse(json);

            T val = (ptr->jsonParser)(json);

            return val;
        }
    public:

        static void checkResponse(const JsonWrapper& json) {
            try {
                if (json.containKey("status")) {
                    std::string status = json.getString("status");
                    if ("error" == status) {
                        std::string err_code = json.getString("err-code");
                        std::string err_msg = json.getString("err-msg");
                        throw HuobiApiException(HuobiApiException::EXEC_ERROR,
                                "[Executing] " + err_code + ": " + err_msg);
                    } else if ("ok" != status) {
                        throw HuobiApiException(
                                HuobiApiException::RUNTIME_ERROR, "[Invoking] Response is not expected: " + status);
                    }
                } else if (json.containKey("success")) {
                    bool success = json.getBool("success");
                    if (!success) {
                        std::string err_code = EtfResult::checkResult(json.getInt("code"));
                        std::string err_msg = json.getString("message");
                        if (err_code.empty()) {
                            throw HuobiApiException(HuobiApiException::EXEC_ERROR, "[Executing] " + err_msg);
                        } else {
                            throw HuobiApiException(HuobiApiException::EXEC_ERROR,
                                    "[Executing] " + err_code + ": " + err_msg);
                        }
                    }
                } else {
                    throw HuobiApiException(
                            HuobiApiException::RUNTIME_ERROR, "[Invoking] Status cannot be found in response.");
                }
            } catch (std::exception e) {
                std::string msg;
                msg = "[Invoking] Unexpected error: ";
                throw HuobiApiException(
                        HuobiApiException::RUNTIME_ERROR, msg + e.what());
            }
        }

        template <typename T>
        static T callSync(RestApi<T>* request) {
            return RestApiInvoke::instance()->callSync_Boost<T>(request);
        }
    };
}

#endif /* RESTAPIINVOKE_H */

