#ifndef WEBSOCKETIMPL_H
#define WEBSOCKETIMPL_H

#include <list>
#include "Huobi/SubscriptionClient.h"
#include "Huobi/SubscriptionOptions.h"
#include "WebSocketApiImpl.h"
#include "WebSocketRequest.h"
#include "WebSocketConnection.h"
#include "WebSocketWatchDog.h"
#include "Huobi/RequestOptions.h"
#include "GetHost.h"
#include "RestApiImpl.h"

namespace Huobi {

    class SubscriptionClientImpl : public SubscriptionClient {
    public:

        SubscriptionClientImpl(
                const std::string& apiKey,
                const std::string& secretKey,
                const SubscriptionOptions& op)
        : ssl_(boost::asio::ssl::context::sslv23_client) {
            apiKey_ = apiKey;
            secretKey_ = secretKey;
            op_ = std::make_shared<SubscriptionOptions>(op);
            watchDog_ = std::make_shared<WebSocketWatchDog>(op_);
            impl_ = std::make_shared<WebSocketApiImpl>(apiKey, secretKey);
            ssl_.load_verify_file("/etc/huobi_cert/cert.pem");

            if (apiKey != "" && secretKey != "") {
                if (!op.url.empty()) {
                    RequestOptions resop;
                    resop.url = op.url;
                    RestApiImpl* restimpl = new RestApiImpl(apiKey.c_str(), secretKey.c_str(), resop);
                    AccountsInfoMap::updateUserInfo(apiKey, restimpl);
                    delete restimpl;
                } else {
                    RestApiImpl* restimpl = new RestApiImpl(apiKey.c_str(), secretKey.c_str());
                    AccountsInfoMap::updateUserInfo(apiKey, restimpl);
                    delete restimpl;
                }
            }
        }

        ~SubscriptionClientImpl() {
        }

        void subscribeCandlestickEvent(
                const char* symbols,
                CandlestickInterval interval,
                const std::function<void(const CandlestickEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler = std::function<void(HuobiApiException&)>()) override;

        void subscribeTradeEvent(
                const char* symbols,
                const std::function<void(const TradeEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler = std::function<void(HuobiApiException&)>()) override;

        void subscribePriceDepthEvent(
                const char* symbols,
                const std::function<void(const PriceDepthEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler = std::function<void(HuobiApiException&)>()) override;

        void subscribe24HTradeStatisticsEvent(
                const char* symbols,
                const std::function<void(const TradeStatisticsEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler = std::function<void(HuobiApiException&)>()) override;

        void subscribeOrderUpdateEvent(
                const char* symbols,
                const std::function<void(const OrderUpdateEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler = std::function<void(HuobiApiException&)>()) override;

        void subscribeAccountEvent(
                const BalanceMode& mode,
                const std::function<void(const AccountEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler = std::function<void(HuobiApiException&)>()) override;

        void startService() override {
            std::for_each(connectionList_.begin(), connectionList_.end(), [](const WebSocketConnectHanlder & handler) {
                handler->connect();
            });
            // Run the I/O service. The call will return when
            // the socket is closed.
            io_.run();
        }

        void stopService() override {
            std::for_each(connectionList_.begin(), connectionList_.end(), [](const WebSocketConnectHanlder & handler) {
                handler->close();
            });
            io_.stop();
        }

    private:
        std::list<std::string> parseSymbols(const char* symbols);

        void createConnection(WebSocketRequest * request) {
            connectionList_.push_back(std::make_shared<WebSocketConnection>(request, apiKey_, secretKey_, op_, io_, ssl_));
        }

        typedef std::list<WebSocketConnectHanlder> WebSocketConnectList;

    private:
        boost::asio::io_context io_;
        boost::asio::ssl::context ssl_;
        WebSocketWatchDogHandler watchDog_;
        WebSocketApiImplHandler impl_;
        WebSocketConnectList connectionList_;

        std::string apiKey_;
        std::string secretKey_;
        SubscriptionOptionsHandler op_;
    };
}



#endif /* WEBSOCKETIMPL_H */

