#ifndef WEBSOCKETIMPL_H
#define WEBSOCKETIMPL_H

#include <list>
#include "Huobi/SubscriptionClient.h"
#include "Huobi/SubscriptionOptions.h"
#include "WebSocketApiImpl.h"
#include "WebSocketRequest.h"
#include "WebSocketConnection.h"
#include "WebSockets/WebSocketsService.h"
#include "WebSocketWatchDog.h"
#include "Huobi/RequestOptions.h"
#include "GetHost.h"
#include "RestApiImpl.h"

namespace Huobi {

    class SubscriptionClientImpl : public SubscriptionClient {
    private:
        WebSocketApiImpl *impl = nullptr;
        WebSocketsServiceHanlder service_;
    public:
        void startService() override;

        SubscriptionClientImpl() {
            service_ = std::make_shared<WebSocketsService>();
            service_->initialize("", "", SubscriptionOptions());
            impl = new WebSocketApiImpl(service_);
        }

        SubscriptionClientImpl(const SubscriptionOptions& op) {
            service_ = std::make_shared<WebSocketsService>();
            service_->initialize("", "", op);
            impl = new WebSocketApiImpl(service_);
        }

        SubscriptionClientImpl(
                std::string apiKey,
                std::string secretKey,
                SubscriptionOptions& op) {
            service_ = std::make_shared<WebSocketsService>();
            service_->initialize(apiKey, secretKey, op);
            impl = new WebSocketApiImpl(service_);
            
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

    private:
        std::list<std::string> parseSymbols(const char* symbols);
    };
}



#endif /* WEBSOCKETIMPL_H */

