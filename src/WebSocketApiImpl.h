#ifndef WEBSOCKETAPIIMPL_H
#define WEBSOCKETAPIIMPL_H

#include <string>
#include <list>
#include "WebSocketRequest.h"
#include "Huobi/CandlestickEvent.h"
#include "Huobi/AccountEvent.h"
#include "Huobi/TradeEvent.h"
#include "Huobi/TradeStatisticsEvent.h"
#include "Huobi/PriceDepthEvent.h"
#include "Huobi/OrderUpdateEvent.h"
#include "Huobi/Enums.h"
#include "WebSockets/WebSocketsService.h"

namespace Huobi {

    class WebSocketApiImpl {
    public:

        WebSocketApiImpl(WebSocketsServiceHanlder service) : service_(service) {
        }

        WebSocketRequest* subscribeCandlestickEvent(
                const std::list<std::string>& symbols,
                CandlestickInterval interval,
                const std::function<void(const CandlestickEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler);

        WebSocketRequest* subscribeTradeEvent(
                const std::list<std::string>& symbols,
                const std::function<void(const TradeEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler);

        WebSocketRequest* subscribePriceDepthEvent(
                const std::list<std::string>& symbols,
                const std::function<void(const PriceDepthEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler);

        WebSocketRequest* subscribe24HTradeStatisticsEvent(
                const std::list<std::string>& symbols,
                const std::function<void(const TradeStatisticsEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler);

        WebSocketRequest* subscribeOrderUpdateEvent(
                const std::list<std::string>& symbols,
                const std::function<void(const OrderUpdateEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler);

        WebSocketRequest * subscribeAccountEvent(
                const BalanceMode& mode,
                const std::function<void(const AccountEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler);
        
    private:
        WebSocketsServiceHanlder service_;
    };

}
#endif /* WEBSOCKETAPIIMPL_H */

