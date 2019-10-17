//#include <string>
//#include <vector>
//#include <libwebsockets.h>
//
//#include "WebSocketApiImpl.h"
//#include "AccountsInfoMap.h"
//#include "WebSocketRequest.h"
//#include "WebSocketConnection.h"
//#include "Utils/Channels.h"
//#include "Utils/ChannelParser.h"
//#include "TimeService.h"
//#include "InputChecker.h"
//
//namespace Huobi {
//
//    WebSocketRequest* WebSocketApiImpl::subscribeCandlestickEvent(
//            const std::list<std::string>& symbols,
//            CandlestickInterval interval,
//            const std::function<void(const CandlestickEvent&) >& callback,
//            const std::function<void(HuobiApiException&)>& errorHandler) {
//
//        InputChecker::checker()
//                ->shouldNotNull(interval.getValue(), "interval")
//                ->checkCallback(callback);
//        auto req = new WebSocketRequestImpl<CandlestickEvent>();
//        req->connectionHandler = [symbols, interval](WebSocketConnection * connection) {
//            for (std::string symbol : symbols) {
//                connection->send(Channels::klineChannel(symbol, interval));
//                std::this_thread::sleep_for(std::chrono::milliseconds(1));
//            }
//        };
//        req->JsonParser = [interval](const JsonWrapper & json) {
//            ChannelParser parser = ChannelParser(json.getString("ch"));
//            CandlestickEvent event;
//            event.symbol = parser.getSymbol();
//            event.interval = interval;
//            event.timestamp = TimeService::convertCSTInMillisecondToUTC(json.getLong("ts"));
//            JsonWrapper tick = json.getJsonObjectOrArray("tick");
//            Candlestick data;
//            data.timestamp = TimeService::convertCSTInSecondToUTC(tick.getLong("id"));
//            data.id = tick.getLong("id");
//            data.amount = tick.getDecimal("amount");
//            data.close = tick.getDecimal("close");
//            data.high = tick.getDecimal("high");
//            data.low = tick.getDecimal("low");
//            data.open = tick.getDecimal("open");
//            data.volume = tick.getDecimal("vol");
//            data.count = tick.getLong("count");
//            event.data = data;
//            return event;
//        };
//        req->isNeedSignature = false;
//        req->Callback = callback;
//        req->errorHandler = errorHandler;
//        return req;
//    }
//
//    WebSocketRequest* WebSocketApiImpl::subscribeTradeEvent(
//            const std::list<std::string>& symbols,
//            const std::function<void(const TradeEvent&) >& callback,
//            const std::function<void(HuobiApiException&)>& errorHandler) {
//        InputChecker::checker()->checkCallback(callback);
//        auto req = new WebSocketRequestImpl<TradeEvent>();
//        req->connectionHandler = [symbols](WebSocketConnection * connection) {
//            for (std::string symbol : symbols) {
//                connection->send(Channels::tradeChannel(symbol));
//                std::this_thread::sleep_for(std::chrono::milliseconds(1));
//            }
//        };
//
//        req->JsonParser = [](const JsonWrapper & json) {
//            ChannelParser parser = ChannelParser(json.getString("ch"));
//            TradeEvent tradeEvent;
//            tradeEvent.symbol = parser.getSymbol();
//            tradeEvent.timestamp = TimeService::convertCSTInMillisecondToUTC(json.getLong("ts"));
//            JsonWrapper tick = json.getJsonObjectOrArray("tick");
//            JsonWrapper dataArray = tick.getJsonObjectOrArray("data");
//            for (int i = 0; i < dataArray.size(); i++) {
//                JsonWrapper item = dataArray.getJsonObjectAt(i);
//                Trade trade;
//                trade.amount = item.getDecimal("amount");
//                trade.price = item.getDecimal("price");
//                trade.tradeId = item.getString("id");
//                trade.direction = TradeDirection::lookup(item.getString("direction"));
//                trade.timestamp = TimeService::convertCSTInMillisecondToUTC(item.getLong("ts"));
//                tradeEvent.tradeList.push_back(trade);
//            }
//            return tradeEvent;
//        };
//
//        req->isNeedSignature = false;
//        req->Callback = callback;
//        req->errorHandler = errorHandler;
//        return req;
//    }
//
//    WebSocketRequest* WebSocketApiImpl::subscribePriceDepthEvent(
//            const std::list<std::string>& symbols,
//            DepthStep step,
//            const std::function<void(const PriceDepthEvent&) >& callback,
//            const std::function<void(HuobiApiException&)>& errorHandler) {
//        InputChecker::checker()->checkCallback(callback);
//
//        auto req = new WebSocketRequestImpl<PriceDepthEvent>();
//
//        req->connectionHandler = [symbols, step](WebSocketConnection * connection) {
//            for (std::string symbol : symbols) {
//                connection->send(Channels::priceDepthChannel(symbol, step));
//                std::this_thread::sleep_for(std::chrono::milliseconds(1));
//            }
//        };
//
//        req->JsonParser = [](const JsonWrapper & json) {
//            ChannelParser parser = ChannelParser(json.getString("ch"));
//            PriceDepthEvent priceDepthEvent;
//            priceDepthEvent.symbol = parser.getSymbol();
//            priceDepthEvent.timestamp = TimeService::convertCSTInMillisecondToUTC(json.getLong("ts"));
//            JsonWrapper tick = json.getJsonObjectOrArray("tick");
//            JsonWrapper bids = tick.getJsonObjectOrArray("bids");
//            JsonWrapper asks = tick.getJsonObjectOrArray("asks");
//            PriceDepth depth;
//            std::vector<DepthEntry>bidsves;
//            for (int i = 0; i < bids.size(); i++) {
//                DepthEntry de;
//                JsonWrapper item = bids.getArrayAt(i);
//                de.price = item.getDecimalAt(0);
//                de.amount = item.getDecimalAt(1);
//                bidsves.push_back(de);
//            }
//            std::vector<DepthEntry>asksves;
//            for (int i = 0; i < asks.size(); i++) {
//                DepthEntry de;
//                JsonWrapper item = asks.getArrayAt(i);
//                de.price = item.getDecimalAt(0);
//                de.amount = item.getDecimalAt(1);
//                asksves.push_back(de);
//            }
//            depth.bids = bidsves;
//            depth.asks = asksves;
//            priceDepthEvent.data = depth;
//            return priceDepthEvent;
//        };
//
//        req->isNeedSignature = false;
//        req->Callback = callback;
//        req->errorHandler = errorHandler;
//        return req;
//    }
//
//    WebSocketRequest* WebSocketApiImpl::subscribe24HTradeStatisticsEvent(
//            const std::list<std::string>& symbols,
//            const std::function<void(const TradeStatisticsEvent&) >& callback,
//            const std::function<void(HuobiApiException&)>& errorHandler) {
//        InputChecker::checker()->checkCallback(callback);
//
//        auto req = new WebSocketRequestImpl<TradeStatisticsEvent>();
//
//        req->connectionHandler = [symbols](WebSocketConnection * connection) {
//            for (std::string symbol : symbols) {
//                connection->send(Channels::tradeStatisticsChannel(symbol));
//                std::this_thread::sleep_for(std::chrono::milliseconds(1));
//            }
//        };
//
//        req->JsonParser = [](const JsonWrapper & json) {
//            ChannelParser parser = ChannelParser(json.getString("ch"));
//            TradeStatisticsEvent tradeStatisticsEvent;
//            tradeStatisticsEvent.symbol = parser.getSymbol();
//            long ts = TimeService::convertCSTInMillisecondToUTC(json.getLong("ts"));
//            tradeStatisticsEvent.timestamp = ts;
//            JsonWrapper tick = json.getJsonObjectOrArray("tick");
//            TradeStatistics statistics;
//            statistics.amount = tick.getDecimal("amount");
//            statistics.open = tick.getDecimal("open");
//            statistics.close = tick.getDecimal("close");
//            statistics.high = tick.getDecimal("high");
//            statistics.timestamp = ts;
//            statistics.count = tick.getLong("count");
//            statistics.low = tick.getDecimal("low");
//            statistics.volume = tick.getDecimal("vol");
//            tradeStatisticsEvent.tradeStatistics = statistics;
//            return tradeStatisticsEvent;
//        };
//
//        req->isNeedSignature = false;
//        req->Callback = callback;
//        req->errorHandler = errorHandler;
//        return req;
//    }
//
//    WebSocketRequest* WebSocketApiImpl::subscribeOrderUpdateEvent(
//            const std::list<std::string>& symbols,
//            const std::function<void(const OrderUpdateEvent&) >& callback,
//            const std::function<void(HuobiApiException&)>& errorHandler) {
//        InputChecker::checker()->checkCallback(callback);
//
//        auto req = new WebSocketRequestImpl<OrderUpdateEvent>();
//
//        req->connectionHandler = [symbols](WebSocketConnection * connection) {
//            for (std::string symbol : symbols) {
//                connection->send(Channels::orderChannel(symbol));
//                std::this_thread::sleep_for(std::chrono::milliseconds(1));
//            }
//        };
//
//        req->JsonParser = [this](const JsonWrapper & json) {
//            ChannelParser parser = ChannelParser(json.getString("topic"));
//            OrderUpdateEvent orderUpdateEvent;
//            orderUpdateEvent.symbol = parser.getSymbol();
//            orderUpdateEvent.timestamp = TimeService::convertCSTInMillisecondToUTC(json.getLong("ts"));
//            JsonWrapper data = json.getJsonObjectOrArray("data");
//            Order order;
//            order.orderId = data.getLong("order-id");
//            order.symbol = parser.getSymbol();           
//            order.accountType = AccountsInfoMap::getAccount(this->accessKey, data.getLong("account-id")).type;
//            order.amount = data.getDecimal("order-amount");
//            order.price = data.getDecimal("order-price");
//            order.createdTimestamp = TimeService::convertCSTInMillisecondToUTC(data.getLong("created-at"));
//            order.type = OrderType::lookup(data.getString("order-type"));
//            order.filledAmount = data.getDecimal("filled-amount");
//            order.filledCashAmount = data.getDecimal("filled-cash-amount");
//            order.filledFees = data.getDecimal("filled-fees");
//            order.state = OrderState::lookup(data.getString("order-state"));
//            order.source = OrderSource::lookup(data.getString("order-source"));
//            orderUpdateEvent.data = order;
//            return orderUpdateEvent;
//        };
//        req->isNeedSignature = true;
//        req->Callback = callback;
//        req->errorHandler = errorHandler;
//        return req;
//    }
//
//    WebSocketRequest* WebSocketApiImpl::subscribeAccountEvent(
//            const BalanceMode& mode,
//            const std::function<void(const AccountEvent&) >& callback,
//            const std::function<void(HuobiApiException&)>& errorHandler) {
//        InputChecker::checker()->checkCallback(callback);
//
//        auto req = new WebSocketRequestImpl<AccountEvent>();
//        req->connectionHandler = [mode](WebSocketConnection * connection) {
//            connection->send(Channels::accountChannel(mode));
//        };
//        req->JsonParser = [this](const JsonWrapper & json) {
//            AccountEvent accountEvent;
//            JsonWrapper data = json.getJsonObjectOrArray("data");
//            accountEvent.changeType = AccountChangeType::lookup(data.getString("event"));
//            accountEvent.timestamp = TimeService::convertCSTInMillisecondToUTC(json.getLong("ts"));
//            JsonWrapper listArray = data.getJsonObjectOrArray("list");
//            for (int i = 0; i < listArray.size(); i++) {
//                JsonWrapper itemInList = listArray.getJsonObjectAt(i);
//                AccountChange change;
//                change.accountType = AccountsInfoMap::getAccount(this->accessKey, itemInList.getLong("account-id")).type;
//                change.currency = itemInList.getString("currency");
//                change.balance = itemInList.getDecimal("balance");
//                change.balanceType = BalanceType::lookup(itemInList.getString("type"));
//                accountEvent.accountChangeList.push_back(change);
//            }
//            return accountEvent;
//        };
//        req->isNeedSignature = true;
//        req->Callback = callback;
//        req->errorHandler = errorHandler;
//        return req;
//
//    }
//
//    WebSocketRequest* WebSocketApiImpl::subscribeOrderUpdateNewEvent(
//            const std::list<std::string>& symbols,
//            const std::function<void(const OrderUpdateEvent&) >& callback,
//            const std::function<void(HuobiApiException&)>& errorHandler) {
//        InputChecker::checker()->checkCallback(callback);
//
//        auto req = new WebSocketRequestImpl<OrderUpdateEvent>();
//
//        req->connectionHandler = [symbols](WebSocketConnection * connection) {
//            for (std::string symbol : symbols) {
//                connection->send(Channels::newOrderChannel(symbol));
//                std::this_thread::sleep_for(std::chrono::milliseconds(1));
//            }
//        };
//
//        req->JsonParser = [this](const JsonWrapper & json) {
//            ChannelParser parser = ChannelParser(json.getString("topic"));
//            OrderUpdateEvent orderUpdateEvent;
//            orderUpdateEvent.symbol = parser.getSymbol();
//            orderUpdateEvent.timestamp = TimeService::convertCSTInMillisecondToUTC(json.getLong("ts"));
//            JsonWrapper data = json.getJsonObjectOrArray("data");
//            Order order;
//            order.orderId = data.getLong("order-id");
//            order.symbol = parser.getSymbol();
//            order.price = data.getDecimal("price");
//            order.type = OrderType::lookup(data.getString("order-type"));
//            order.filledAmount = data.getDecimal("filled-amount");
//            order.filledCashAmount = data.getDecimal("filled-cash-amount");
//            order.state = OrderState::lookup(data.getString("order-state"));
//            orderUpdateEvent.match_id = data.getLong("match-id");
//            orderUpdateEvent.client_order_id = data.getString("client-order-id");
//            orderUpdateEvent.role = DealRole::lookup(data.getString("role"));
//            orderUpdateEvent.unfilled_amount = data.getDecimal("unfilled-amount");
//            orderUpdateEvent.data = order;
//            return orderUpdateEvent;
//        };
//        req->isNeedSignature = true;
//        req->Callback = callback;
//        req->errorHandler = errorHandler;
//        return req;
//    }
//
//    WebSocketRequest* WebSocketApiImpl::subscribeMarketBBOEvent(
//            const std::list<std::string>& symbols,
//            const std::function<void(const MarketBBOEvent&) >& callback,
//            const std::function<void(HuobiApiException&)>& errorHandler) {
//        InputChecker::checker()->checkCallback(callback);
//        auto req = new WebSocketRequestImpl<MarketBBOEvent>();
//        req->connectionHandler = [symbols](WebSocketConnection * connection) {
//            for (std::string symbol : symbols) {
//                connection->send(Channels::marketBBOChannel(Channels::OP_SUB, symbol));
//                std::this_thread::sleep_for(std::chrono::milliseconds(1));
//            }
//        };
//
//        req->JsonParser = [](const JsonWrapper & json) {
//            ChannelParser parser = ChannelParser(json.getString("ch"));
//            MarketBBOEvent event;
//            event.symbol = parser.getSymbol();
//            long ts = TimeService::convertCSTInMillisecondToUTC(json.getLong("ts"));
//            event.timestamp = ts;
//            JsonWrapper tick = json.getJsonObjectOrArray("tick");
//            BestQuote bbo;
//            bbo.askAmount = tick.getDecimal("askSize");
//            bbo.askPrice = tick.getDecimal("ask");
//            bbo.bidAmount = tick.getDecimal("bidSize");
//            bbo.bidPrice = tick.getDecimal("bid");
//            bbo.timestamp = TimeService::convertCSTInMillisecondToUTC(tick.getLong("quoteTime"));
//            event.bbo = bbo;
//            return event;
//        };
//
//        req->isNeedSignature = false;
//        req->Callback = callback;
//        req->errorHandler = errorHandler;
//        return req;
//
//    }
//
//    WebSocketRequest* WebSocketApiImpl::requestCandlestickEvent(
//            bool autoClose,
//            const std::list<std::string>& symbols,
//            CandlestickInterval interval,
//            long startTime,
//            long endTime,
//            const std::function<void(const std::vector<CandlestickEvent>&) >& callback,
//            const std::function<void(HuobiApiException&)>& errorHandler) {
//
//        InputChecker::checker()
//                ->shouldNotNull(interval.getValue(), "interval")
//                ->checkCallback(callback);
//        auto req = new WebSocketRequestImpl<std::vector < CandlestickEvent >> ();
//        req->autoClose = autoClose;
//        req->time = symbols.size();
//        req->connectionHandler = [symbols, interval, startTime, endTime](WebSocketConnection * connection) {
//            for (std::string symbol : symbols) {
//                connection->send(Channels::klineChannel(Channels::OP_REQ, symbol, interval, startTime, endTime));
//                std::this_thread::sleep_for(std::chrono::milliseconds(1));
//            }
//        };
//        req->JsonParser = [interval](const JsonWrapper & json) {
//            std::vector<CandlestickEvent> cans;
//            JsonWrapper data = json.getJsonObjectOrArray("data");
//            for (int i = 0; i < data.size(); i++) {
//                JsonWrapper item = data.getJsonObjectAt(i);
//                CandlestickEvent candlestickEvent;
//                ChannelParser parser = ChannelParser(json.getString("rep"));
//                candlestickEvent.symbol = parser.getSymbol();
//                candlestickEvent.interval = interval;
//                Candlestick can;
//                can.timestamp = TimeService::convertCSTInSecondToUTC(item.getLong("id"));
//                can.id = item.getLong("id");
//                can.amount = item.getDecimal("amount");
//                can.close = item.getDecimal("close");
//                can.high = item.getDecimal("high");
//                can.low = item.getDecimal("low");
//                can.open = item.getDecimal("open");
//                can.volume = item.getDecimal("vol");
//                can.count = item.getLong("count");
//                candlestickEvent.data = can;
//                candlestickEvent.timestamp = can.timestamp;
//                cans.push_back(candlestickEvent);
//            }
//            return cans;
//        };
//        req->isNeedSignature = false;
//        req->Callback = callback;
//        req->errorHandler = errorHandler;
//        return req;
//    }
//
//    WebSocketRequest* WebSocketApiImpl::requestPriceDepthEvent(
//            bool autoClose,
//            const std::list<std::string>& symbols,
//            DepthStep step,
//            const std::function<void(const PriceDepthEvent&) >& callback,
//            const std::function<void(HuobiApiException&)>& errorHandler) {
//        InputChecker::checker()
//                ->checkCallback(callback);
//        auto req = new WebSocketRequestImpl<PriceDepthEvent> ();
//        req->connectionHandler = [symbols, step](WebSocketConnection * connection) {
//            for (std::string symbol : symbols) {
//                connection->send(Channels::priceDepthChannel(Channels::OP_REQ, symbol, step));
//                std::this_thread::sleep_for(std::chrono::milliseconds(1));
//            }
//        };
//        req->autoClose = autoClose;
//        req->time = symbols.size();
//        req->JsonParser = [](const JsonWrapper & json) {
//            PriceDepthEvent event;
//            PriceDepth priceDepth;
//            JsonWrapper data = json.getJsonObjectOrArray("data");
//            JsonWrapper bids = data.getJsonObjectOrArray("bids");
//            JsonWrapper asks = data.getJsonObjectOrArray("asks");
//            std::vector<DepthEntry>bidsves;
//            for (int i = 0; i < bids.size(); i++) {
//                DepthEntry de;
//                JsonWrapper item = bids.getArrayAt(i);
//                de.price = item.getDecimalAt(0);
//                de.amount = item.getDecimalAt(1);
//                bidsves.push_back(de);
//            }
//            std::vector<DepthEntry>asksves;
//            for (int i = 0; i < asks.size(); i++) {
//                DepthEntry de;
//                JsonWrapper item = asks.getArrayAt(i);
//                de.price = item.getDecimalAt(0);
//                de.amount = item.getDecimalAt(1);
//                asksves.push_back(de);
//            }
//            priceDepth.bids = bidsves;
//            priceDepth.asks = asksves;
//            event.data = priceDepth;
//            ChannelParser parser = ChannelParser(json.getString("rep"));
//            event.symbol = parser.getSymbol();
//            event.timestamp = TimeService::convertCSTInMillisecondToUTC(json.getLong("ts"));
//            return event;
//        };
//        req->isNeedSignature = false;
//        req->Callback = callback;
//        req->errorHandler = errorHandler;
//        return req;
//    }
//
//    WebSocketRequest* WebSocketApiImpl::requestTradeEvent(
//            bool autoClose,
//            const std::list<std::string>& symbols,
//            const std::function<void(const TradeEvent&) >& callback,
//            const std::function<void(HuobiApiException&)>& errorHandler) {
//        InputChecker::checker()
//                ->checkCallback(callback);
//        auto req = new WebSocketRequestImpl<TradeEvent>();
//        req->autoClose = autoClose;
//        req->time = symbols.size();
//        req->connectionHandler = [symbols](WebSocketConnection * connection) {
//            for (std::string symbol : symbols) {
//                connection->send(Channels::tradeChannel(Channels::OP_REQ, symbol));
//                std::this_thread::sleep_for(std::chrono::milliseconds(1));
//            }
//
//        };
//        req->JsonParser = [symbols](const JsonWrapper & json) {
//            TradeEvent event;
//            std::vector<Trade> tradeVec;
//            JsonWrapper dataArray = json.getJsonObjectOrArray("data");
//            for (int i = 0; i < dataArray.size(); i++) {
//                JsonWrapper item = dataArray.getJsonObjectAt(i);
//                Trade trade;
//                trade.amount = item.getDecimal("amount");
//                trade.price = item.getDecimal("price");
//                trade.tradeId = item.getString("id");
//                trade.direction = TradeDirection::lookup(item.getString("direction"));
//                trade.timestamp = TimeService::convertCSTInMillisecondToUTC(item.getLong("ts"));
//                tradeVec.push_back(trade);
//            }
//            event.tradeList = tradeVec;
//            ChannelParser parser = ChannelParser(json.getString("rep"));
//            event.symbol = parser.getSymbol();
//            event.timestamp = TimeService::convertCSTInMillisecondToUTC(json.getLong("id"));
//            return event;
//        };
//
//        req->isNeedSignature = false;
//        req->Callback = callback;
//        req->errorHandler = errorHandler;
//        return req;
//    }
//
//    WebSocketRequest* WebSocketApiImpl::request24HTradeStatistics(
//            bool autoClose,
//            const std::list<std::string>& symbols,
//            const std::function<void(const TradeStatisticsEvent&) >& callback,
//            const std::function<void(HuobiApiException&)>& errorHandler) {
//        InputChecker::checker()
//                ->checkCallback(callback);
//        auto req = new WebSocketRequestImpl<TradeStatisticsEvent>();
//        req->autoClose = autoClose;
//        req->time = symbols.size();
//        req->connectionHandler = [symbols](WebSocketConnection * connection) {
//            for (std::string symbol : symbols) {
//                connection->send(Channels::tradeStatisticsChannel(Channels::OP_REQ, symbol));
//                std::this_thread::sleep_for(std::chrono::milliseconds(1));
//            }
//        };
//        req->JsonParser = [](const JsonWrapper & json) {
//            TradeStatisticsEvent event;
//            JsonWrapper data = json.getJsonObjectOrArray("data");
//            long ts = TimeService::convertCSTInMillisecondToUTC(json.getLong("ts"));
//            TradeStatistics statistics;
//            statistics.amount = data.getDecimal("amount");
//            statistics.open = data.getDecimal("open");
//            statistics.close = data.getDecimal("close");
//            statistics.high = data.getDecimal("high");
//            statistics.timestamp = ts;
//            statistics.count = data.getLong("count");
//            statistics.low = data.getDecimal("low");
//            statistics.volume = data.getDecimal("vol");
//            event.tradeStatistics = statistics;
//            ChannelParser parser = ChannelParser(json.getString("rep"));
//            event.symbol = parser.getSymbol();
//            event.timestamp = ts;
//            return event;
//        };
//
//        req->isNeedSignature = false;
//        req->Callback = callback;
//        req->errorHandler = errorHandler;
//        return req;
//    }
//
//    WebSocketRequest* WebSocketApiImpl::requestAccountList(
//            bool autoClose,
//            const std::function<void(const AccountListEvent&) >& callback,
//            const std::function<void(HuobiApiException&)>& errorHandler) {
//
//        InputChecker::checker()
//                ->checkCallback(callback);
//        auto req = new WebSocketRequestImpl<AccountListEvent>();
//        req->autoClose = autoClose;
//        req->time = 1;
//        req->connectionHandler = [](WebSocketConnection * connection) {
//            connection->send(Channels::accountListChannel(Channels::OP_REQ));
//        };
//        req->JsonParser = [](const JsonWrapper & json) {
//            AccountListEvent event;
//            JsonWrapper data = json.getJsonObjectOrArray("data");
//            long ts = TimeService::convertCSTInMillisecondToUTC(json.getLong("ts"));
//            event.timestamp = ts;
//            for (int i = 0; i < data.size(); i++) {
//                JsonWrapper item = data.getJsonObjectAt(i);
//                Account account;
//                account.id = item.getLong("id");
//                account.type = AccountType::lookup(item.getString("type"));
//                account.state = AccountState::lookup(item.getString("state"));
//                JsonWrapper list = item.getJsonObjectOrArray("list");
//                for (int i = 0; i < list.size(); i++) {
//                    JsonWrapper json = list.getJsonObjectAt(i);
//                    Balance balance;
//                    balance.balance = json.getDecimal("balance");
//                    balance.currency = json.getString("currency");
//                    balance.type = BalanceType::lookup(json.getString("type"));
//                    account.balances.push_back(balance);
//                }
//                event.accounts.push_back(account);
//            }
//            return event;
//        };
//        req->isNeedSignature = true;
//        req->Callback = callback;
//        req->errorHandler = errorHandler;
//        return req;
//    }
//
//    WebSocketRequest* WebSocketApiImpl::requestOrdertListEvent(
//            bool autoClose,
//            long accountId,
//            const std::list<std::string>& symbols,
//            OrderType types,
//            OrderState states,
//            long startTime,
//            long endTime,
//            long fromId,
//            QueryDirection direction,
//            int size,
//            const std::function<void(const OrderListEvent&) >& callback,
//            const std::function<void(HuobiApiException&)>& errorHandler) {
//        InputChecker::checker()
//                ->shouldBiggerThanZero(accountId, "accountId")
//                ->checkCallback(callback);
//        auto req = new WebSocketRequestImpl<OrderListEvent>();
//        req->autoClose = autoClose;
//        req->time = symbols.size();
//        req->connectionHandler = [symbols, accountId, types, states, startTime, endTime, fromId, direction, size](WebSocketConnection * connection) {
//            for (std::string symbol : symbols) {
//                connection->send(Channels::orderListChannel(Channels::OP_REQ, accountId, symbol, types, states, startTime, endTime, fromId, direction, size));
//                std::this_thread::sleep_for(std::chrono::milliseconds(1));
//            }
//        };
//        req->JsonParser = [this](const JsonWrapper & json) {
//            OrderListEvent event;
//            JsonWrapper data = json.getJsonObjectOrArray("data");
//            long ts = TimeService::convertCSTInMillisecondToUTC(json.getLong("ts"));
//            event.timestamp = ts;
//            for (int i = 0; i < data.size(); i++) {
//                JsonWrapper item = data.getJsonObjectAt(i);
//                Order order;
//                order.orderId = item.getLong("id");
//                order.symbol = item.getString("symbol");
//                order.price = item.getDecimal("price");
//                order.amount = item.getDecimal("amount");
//                order.accountType =
//                        AccountsInfoMap::getAccount(this->accessKey, item.getLong("account-id")).type;             
//                order.createdTimestamp =
//                        TimeService::convertCSTInMillisecondToUTC(item.getLong("created-at"));
//                order.type = OrderType::lookup(item.getString("type"));
//                order.filledAmount = item.getDecimal("filled-amount");
//                order.filledCashAmount = item.getDecimal("filled-cash-amount");
//                order.filledFees = item.getDecimal("filled-fees");
//                order.source = OrderSource::lookup(item.getString("source"));
//                order.state = OrderState::lookup(item.getString("state"));
//                order.canceledTimestamp =
//                        TimeService::convertCSTInMillisecondToUTC(item.getLong("canceled-at"));
//                event.orders.push_back(order);        
//            }
//            return event;
//        };
//        req->isNeedSignature = true;
//        req->Callback = callback;
//        req->errorHandler = errorHandler;
//        return req;
//    }
//
//    WebSocketRequest* WebSocketApiImpl::requestOrdertDetailEvent(
//            bool autoClose,
//            long orderId,
//            const std::function<void(const OrderDetailEvent&) >& callback,
//            const std::function<void(HuobiApiException&)>& errorHandler) {
//        InputChecker::checker()
//                ->shouldBiggerThanZero(orderId, "orderId")
//                ->checkCallback(callback);
//        auto req = new WebSocketRequestImpl<OrderDetailEvent>();
//        req->autoClose = autoClose;
//        req->time = 1;
//        req->connectionHandler = [orderId](WebSocketConnection * connection) {
//            connection->send(Channels::orderDetailChannel(Channels::OP_REQ, orderId));
//        };
//        req->JsonParser = [this](const JsonWrapper & json) {
//            OrderDetailEvent event;
//            JsonWrapper data = json.getJsonObjectOrArray("data");
//            long ts = TimeService::convertCSTInMillisecondToUTC(json.getLong("ts"));
//            event.timestamp = ts;
//            Order order;
//            order.orderId = data.getLong("id");
//            order.symbol = data.getString("symbol");
//            order.price = data.getDecimal("price");
//            order.amount = data.getDecimal("amount");
//            order.accountType =
//                    AccountsInfoMap::getAccount(this->accessKey, data.getLong("account-id")).type;
//            order.createdTimestamp =
//                    TimeService::convertCSTInMillisecondToUTC(data.getLong("created-at"));
//            order.type = OrderType::lookup(data.getString("type"));
//            order.filledAmount = data.getDecimal("filled-amount");
//            order.filledCashAmount = data.getDecimal("filled-cash-amount");
//            order.filledFees = data.getDecimal("filled-fees");
//            order.source = OrderSource::lookup(data.getString("source"));
//            order.state = OrderState::lookup(data.getString("state"));
//            order.canceledTimestamp =
//                    TimeService::convertCSTInMillisecondToUTC(data.getLong("canceled-at"));
//            event.order = order;
//            return event;
//        };
//        req->isNeedSignature = true;
//        req->Callback = callback;
//        req->errorHandler = errorHandler;
//        return req;
//
//    }
//
//
//}
//
