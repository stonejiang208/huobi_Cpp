#ifndef WEBSOCKETCONNETION_H
#define WEBSOCKETCONNETION_H

#include <memory>
#include <list>
#include <string>
#include <mutex>

#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/beast.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/asio/strand.hpp>

#include "Huobi/Logger.h"
#include "Huobi/Enums.h"

#include "Utils/JsonWrapper.h"
#include "Utils/gzip.h"
#include "WebSocketRequest.h"
#include "TimeService.h"

namespace Huobi {

    class WebSocketsService;
    
    typedef enum LINESTATUS {
        LINE_CONNECTED, // Connected to server, assume the line status is fine.
        LINE_IDEL, // Initialize status, or closed by normal case, such as manually close.
        LINE_CLOSED_ON_ERROR, // Line closed on error.
        LINE_CONNECTING, // Connecting to server, not finished yet. Once finished, it will be changed to LINE_CONNECTED.
        LINE_DISCONNECTING, // Disconnecting from server, not finished yet. Once finished, it will be changed to LINE_IDEL.
        LINE_DELAY, // Trying to re-connect to server, but still in delay time.
    } LineStatus;

    namespace beast = boost::beast; // from <boost/beast.hpp>
    namespace asio = boost::asio; // from <boost/asio.hpp>
    namespace net = boost::asio::ip; // from <boost/asio/ip/tcp.hpp>

    typedef std::shared_ptr<WebSocketConnection> WebSocketConnectHanlder;
    
    class WebSocketConnection : public std::enable_shared_from_this<WebSocketConnection> {
    public:
        WebSocketConnection(
                WebSocketRequest* request,
                WebSocketsService* service);

        void connect();
        void disconnect();
        void reConnect();
        void reConnect(int delayInSecond);
        void close();
        void onMessage(const char* message);
        void send(const std::string& message);
        long getLastReceivedTime();

        LineStatus getLineStatus() {
            return lineStatus_;
        }

    private:
        std::string createSignature();
        void onReceive(JsonWrapper& json);
        void processPingOnTradingLine(JsonWrapper& json);
        void processPingOnMarketLine(JsonWrapper& json);
        
    private:
        void on_resolve(beast::error_code ec, net::tcp::resolver::results_type results);
        void on_connect(beast::error_code ec, net::tcp::resolver::results_type::endpoint_type);
        void on_read(beast::error_code ec, std::size_t bytes_transferred);
        void on_handshake(beast::error_code ec);
        void on_ssl_handshake(beast::error_code ec);
        void on_write(beast::error_code ec, std::size_t bytes_transferred);

    private:
        std::string apiKey;
        std::string secretKey;
        std::unique_ptr<WebSocketRequest> request;
        std::atomic<LineStatus> lineStatus_;
        long lastReceivedTime_ = 0;
        int delayInSecond = 0;
        std::string host;
        std::string subscriptionMarketUrl = "wss://api.huobi.pro/ws";
        std::string subscriptionTradingUrl = "wss://api.huobi.pro/ws/v1";
        int connectionId;

        WebSocketsService* service_;

        net::tcp::resolver resolver_;
        beast::websocket::stream<
        beast::ssl_stream<beast::tcp_stream>> ws_;
        beast::flat_buffer buffer_;


        static int connectionCounter;
    };
}
#endif /* WEBSOCKETCONNETION_H */

