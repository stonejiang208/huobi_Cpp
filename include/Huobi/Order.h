//#ifndef ORDER_H
//#define ORDER_H
//
//#include <string>
//#include "Huobi/Enums.h"
//#include "Huobi/Decimal.h"
//#include "/root/huobi_Cpp/src/AccountsInfoMap.h"
//namespace Huobi {
//
//    /**
//     * The detail order information.
//     */
//    struct Order {
//        /**
//         * The account type which created this order.
//         */
//        AccountType accountType;
//
//        /**
//         * The amount of base currency in this order.
//         */
//        Decimal amount;
//
//        /**
//         * The limit price of limit order.
//         */
//        Decimal price;
//
//        /**
//         * The UNIX formatted timestamp in UTC when the order was created.
//         */
//        long createdTimestamp = 0;
//
//        /**
//         * The UNIX formatted timestamp in UTC when the order was canceled, if not canceled then has value of 0.
//         */
//        long canceledTimestamp = 0;
//
//        /**
//         * The UNIX formatted timestamp in UTC when the order was changed to a final state. This is not the time the order is matched.
//         */
//        long finishedTimestamp = 0;
//
//        /**
//         * The order id.
//         */
//        long orderId = 0;
//
//        /**
//         * The symbol, like "btcusdt".
//         */
//        std::string symbol;
//
//        /**
//         * The order type, possible values are: buy-market, sell-market, buy-limit, sell-limit, buy-ioc, sell-ioc, buy-limit-maker, sell-limit-maker.
//         */
//        OrderType type;
//
//        /**
//         * The amount which has been filled.
//         */
//        Decimal filledAmount;
//
//        /**
//         * The filled total in quote currency.
//         */
//        Decimal filledCashAmount;
//
//        /**
//         * The transaction fee paid so far.
//         */
//        Decimal filledFees;
//
//        /**
//         * The source where the order was triggered, possible values: sys, web, api, app.
//         */
//        OrderSource source;
//
//        /**
//         * The order state: submitted, partial-filled, cancelling, filled, canceled.
//         */
//        OrderState state;
//
//        /**
//         * The stop price: the trigger price of buy stop limit ,sell stop limit.
//         */
//        Decimal stopPrice;
//
//        /**
//         * The stop operator: buy stop limit or sell stop limit .
//         */
//        StopOrderOperator stopOrderOperator;
//
//        /**
//         * The next time for query ,it exists only if size out of range .
//         */
//        long nextTime = 0;
//
//        static RestApiJsonParser<std::vector<Order> > getDataListParser(std::string accessKey) {
//            RestApiJsonParser<std::vector < Order>> res;
//            res.parseJson = [accessKey](JsonWrapper json) {
//                std::vector<Order> orderList;
//                JsonWrapper data = json.getJsonObjectOrArray("data");
//                for (int i = 0; i < data.size(); i++) {
//                    JsonWrapper item = data.getJsonObjectAt(i);
//                    Order order = parse(item, accessKey);
//                    orderList.push_back(order);
//                }
//                return orderList;
//            };
//            return res;
//        }
//
//        static RestApiJsonParser<std::vector<Order> > getDataFieldListParser(std::string accessKey) {
//            RestApiJsonParser<std::vector < Order>> res;
//            res.parseJson = [accessKey](JsonWrapper json) {
//                std::vector<Order> orderList;
//                JsonWrapper data = json.getJsonObjectOrArray("data");
//                for (int i = 0; i < data.size(); i++) {
//                    JsonWrapper item = data.getJsonObjectAt(i);
//                    Order order = parseField(item, accessKey);
//                    orderList.push_back(order);
//                }
//                return orderList;
//            };
//            return res;
//        }
//
//        static RestApiJsonParser<Order > getDataParser(std::string accessKey) {
//            RestApiJsonParser<Order> res;
//            res.parseJson = [accessKey](JsonWrapper json) {
//                JsonWrapper data = json.getJsonObjectOrArray("data");
//                Order order = parse(json, accessKey);
//                return order;
//            };
//            return res;
//        }
//
//        static RestApiJsonParser<Order > getDataFieldParser(std::string accessKey) {
//            RestApiJsonParser<Order> res;
//            res.parseJson = [accessKey](JsonWrapper json) {
//                JsonWrapper data = json.getJsonObjectOrArray("data");
//                Order order = parseField(data, accessKey);
//                return order;
//            };
//            return res;
//        }
//
//        static Order parse(JsonWrapper item, std::string accessKey) {
//            Order order;
//            order.orderId = item.getLong("id");
//            order.symbol = item.getString("symbol");
//            order.price = item.getDecimal("price");
//            order.amount = item.getDecimal("amount");
//            order.accountType =
//                    AccountsInfoMap::getAccount(accessKey, item.getLong("account-id")).type;
//            order.createdTimestamp =
//                    TimeService::convertCSTInMillisecondToUTC(item.getLong("created-at"));
//            order.type = OrderType::lookup(item.getString("type"));
//            order.filledAmount = item.getDecimal("filled-amount");
//            order.filledCashAmount = item.getDecimal("filled-cash-amount");
//            order.filledFees = item.getDecimal("filled-fees");
//            order.source = OrderSource::lookup(item.getString("source"));
//            order.state = OrderState::lookup(item.getString("state"));
//            order.canceledTimestamp = TimeService::convertCSTInMillisecondToUTC(item.getLongOrDefault("canceled-at", 0));
//            order.finishedTimestamp =
//                    TimeService::convertCSTInMillisecondToUTC(item.getLongOrDefault("finished-at", 0));
//            return order;
//        }
//
//        static Order parseField(JsonWrapper data, std::string accessKey) {
//            Order order;
//            order.symbol = data.getString("symbol");
//            order.orderId = data.getLong("id");
//            order.accountType = AccountsInfoMap::getAccount(accessKey, data.getLong("account-id")).type;
//            order.amount = data.getDecimal("amount");
//            order.canceledTimestamp = TimeService::convertCSTInMillisecondToUTC(data.getLong("canceled-at"));
//            order.createdTimestamp =
//                    TimeService::convertCSTInMillisecondToUTC(data.getLong("created-at"));
//            order.finishedTimestamp =
//                    TimeService::convertCSTInMillisecondToUTC(data.getLong("finished-at"));
//            order.filledAmount = data.getDecimal("field-amount");
//            order.filledCashAmount = data.getDecimal("field-cash-amount");
//            order.filledFees = data.getDecimal("field-fees");
//            order.price = data.getDecimal("price");
//            order.source = OrderSource::lookup(data.getString("source"));
//            order.state = OrderState::lookup(data.getString("state"));
//            order.type = OrderType::lookup(data.getString("type"));
//            order.stopPrice = data.getDecimalOrDefault("stop-price", Decimal(0));
//            if (data.containKey("operator")) {
//                order.stopOrderOperator = StopOrderOperator::lookup(data.getString("operator"));
//            }
//            order.nextTime = TimeService::convertCSTInMillisecondToUTC(data.getLongOrDefault("next-time", 0));
//            return order;
//        }
//
//    };
//
//}
//
//
//#endif /* ORDER_H */
//
