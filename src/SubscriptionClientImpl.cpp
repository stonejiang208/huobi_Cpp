#include <sstream>
#include "SubscriptionClientImpl.h"
#include "WebSocketConnection.h"
#include "InputChecker.h"

namespace Huobi {

//    static int event_cb(
//            struct lws* wsi,
//            enum lws_callback_reasons reason,
//            void* user,
//            void* in,
//            size_t len) {
//        WebSocketConnection* connection = reinterpret_cast<WebSocketConnection*> (user);
//        switch (reason) {
//            case LWS_CALLBACK_CLIENT_ESTABLISHED:
//                connection->onOpen(wsi);
//                break;
//            case LWS_CALLBACK_CLIENT_WRITEABLE:
//            {
//                bool flag = connection->flushSendBuffer(wsi);
//                if (!flag) {
//                    //lws_cancel_service_pt(wsi);
//                    return 1;
//                }
//                break;
//            }
//            case LWS_CALLBACK_CLIENT_RECEIVE:
//            {
//                // lwsl_user("receive");
//                char buf[4096*4] = {0};
//                unsigned int l = 4096*4;
//                l = gzDecompress((char*) in, len, buf, l);
//                //lwsl_user("RX %d: %s\n", l, (const char *) buf);
//                connection->onMessage(buf);
//                break;
//            }
//            case LWS_CALLBACK_CLIENT_CLOSED:
//
//                //connection->close();
//                lwsl_user("afer canceled.....\n");
//                connection->disconnect();
//                return 1;
//                //case LWS_CALLBACK_WSI_DESTROY:
//            case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
//                connection->disconnect();
//                lwsl_user("closed... \n");
//                return 1;
//            default:
//                lwsl_notice("notice %d\n", reason);
//                break;
//        }
//
//        return 0;
//    }
//
//    static const struct lws_protocols protocols[] = {
//        {
//            "example-protocol",
//            event_cb,
//            0,
//            0
//        },
//        { NULL, NULL, 0, 0}
//    };
//    static struct lws_context* context = nullptr;

    void SubscriptionClientImpl::startService() {
        std::list<std::shared_ptr<WebSocketConnection>>::iterator it = connectionList.begin();
        for (; it != connectionList.end(); ++it) {
            (*it)->connect();
        }
        context_->startService();
    }

    void SubscriptionClientImpl::createConnection(WebSocketRequest* request) {
        if (context_ == nullptr) {
            context_ = new WebSocketsService();
        }
        if (dog == nullptr) {
            dog = new WebSocketWatchDog(op);
        }
        Logger::LogInfo("createConnection");
        auto connection = std::make_shared<WebSocketConnection>(
                this->apiKey, this->secretKey, request,context_, host);
        connectionList.push_back(connection);
    }

    std::list<std::string> SubscriptionClientImpl::parseSymbols(const char* symbols) {

        std::string input(symbols);
        std::list<std::string> res;
        std::stringstream ss(input);
        std::string temp;
        while (std::getline(ss, temp, ',')) {
            InputChecker::checker()->checkSymbol(temp);
            res.push_back(temp);
        }
        return res;
    }

    void SubscriptionClientImpl::subscribeCandlestickEvent(
            const char* symbols,
            CandlestickInterval interval,
            const std::function<void(const CandlestickEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        createConnection(impl->subscribeCandlestickEvent(parseSymbols(symbols), interval, callback, errorHandler));
    }

    void SubscriptionClientImpl::subscribeTradeEvent(
            const char* symbols,
            const std::function<void(const TradeEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        createConnection(impl->subscribeTradeEvent(parseSymbols(symbols), callback, errorHandler));
    }

    void SubscriptionClientImpl::subscribePriceDepthEvent(
            const char* symbols,
            const std::function<void(const PriceDepthEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        createConnection(impl->subscribePriceDepthEvent(parseSymbols(symbols), callback, errorHandler));
    }

    void SubscriptionClientImpl::subscribe24HTradeStatisticsEvent(
            const char* symbols,
            const std::function<void(const TradeStatisticsEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        createConnection(impl->subscribe24HTradeStatisticsEvent(parseSymbols(symbols), callback, errorHandler));
    }

    void SubscriptionClientImpl::subscribeOrderUpdateEvent(
            const char* symbols,
            const std::function<void(const OrderUpdateEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        createConnection(impl->subscribeOrderUpdateEvent(parseSymbols(symbols), callback, errorHandler));
    }

    void SubscriptionClientImpl::subscribeAccountEvent(
            const BalanceMode& mode,
            const std::function<void(const AccountEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        createConnection(impl->subscribeAccountEvent(mode, callback, errorHandler));
    }



}


