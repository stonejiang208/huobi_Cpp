#include <sstream>
#include "SubscriptionClientImpl.h"
#include "WebSocketConnection.h"
#include "InputChecker.h"

namespace Huobi {

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
        createConnection(impl_->subscribeCandlestickEvent(parseSymbols(symbols), interval, callback, errorHandler));
    }

    void SubscriptionClientImpl::subscribeTradeEvent(
            const char* symbols,
            const std::function<void(const TradeEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        createConnection(impl_->subscribeTradeEvent(parseSymbols(symbols), callback, errorHandler));
    }

    void SubscriptionClientImpl::subscribePriceDepthEvent(
            const char* symbols,
            const std::function<void(const PriceDepthEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        createConnection(impl_->subscribePriceDepthEvent(parseSymbols(symbols), callback, errorHandler));
    }

    void SubscriptionClientImpl::subscribe24HTradeStatisticsEvent(
            const char* symbols,
            const std::function<void(const TradeStatisticsEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        createConnection(impl_->subscribe24HTradeStatisticsEvent(parseSymbols(symbols), callback, errorHandler));
    }

    void SubscriptionClientImpl::subscribeOrderUpdateEvent(
            const char* symbols,
            const std::function<void(const OrderUpdateEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        createConnection(impl_->subscribeOrderUpdateEvent(parseSymbols(symbols), callback, errorHandler));
    }

    void SubscriptionClientImpl::subscribeAccountEvent(
            const BalanceMode& mode,
            const std::function<void(const AccountEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        createConnection(impl_->subscribeAccountEvent(mode, callback, errorHandler));
    }



}


