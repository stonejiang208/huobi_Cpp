//#ifndef MATCHRESULT_H
//#define MATCHRESULT_H
//
//#include <string>
//#include "Huobi/Enums.h"
//#include "Huobi/Decimal.h"
//namespace Huobi {
//
//    /**
//     * The match result information.
//     */
//    struct MatchResult {
//        /**
//         * The UNIX formatted timestamp in UTC when the match and fill is done.
//         */
//        long createdTimestamp;
//
//        /**
//         * The amount which has been filled.
//         */
//        Decimal filledAmount;
//
//        /**
//         * The transaction fee paid so far.
//         */
//        Decimal filledFeeds;
//
//        /**
//         * The internal id.
//         */
//        long id;
//
//        /**
//         * The match id of this match.
//         */
//        long matchId;
//
//        /**
//         * The order id of this order.
//         */
//        long orderId;
//
//        /**
//         * The limit price of limit order.
//         */
//        Decimal price;
//
//        /**
//         * The source where the order was triggered, possible values: sys, web, api, app.
//         */
//        OrderSource source;
//
//        /**
//         * The symbol, like "btcusdt".
//         */
//        std::string symbol;
//
//        /**
//         * The order type, possible values are: buy-market, sell-market, buy-limit, sell-limit,
//         * buy-ioc, sell-ioc, buy-limit-maker, sell-limit-maker.
//         */
//        OrderType type;
//
//        /**
//         * The deal role, possible values are: maker,taker.
//         */
//        DealRole role;
//        /**
//         * The deduction quantity.
//         */
//        Decimal filled_points;
//        /**
//         * The deduction currency, like ht, hbpoint
//         */
//        std::string fee_deduct_currency;
//
//        static RestApiJsonParser<std::vector<MatchResult> > getDataParser() {
//            RestApiJsonParser<std::vector < MatchResult>> res;
//            res.parseJson = [](JsonWrapper json) {
//                std::vector<MatchResult> matchResultList;
//                JsonWrapper data = json.getJsonObjectOrArray("data");
//                for (int i = 0; i < data.size(); i++) {
//                    JsonWrapper item = data.getJsonObjectAt(i);
//                    MatchResult matchResult = parse(item);
//                    matchResultList.push_back(matchResult);
//                }
//                return matchResultList;
//            };
//            return res;
//        }
//
//        static MatchResult parse(JsonWrapper item) {
//            MatchResult matchResult;
//            matchResult.id = (item.getLong("id"));
//            matchResult.createdTimestamp =
//                    TimeService::convertCSTInMillisecondToUTC(item.getLong("created-at"));
//            matchResult.filledAmount = item.getDecimal("filled-amount");
//            matchResult.filledFeeds = item.getDecimal("filled-fees");
//            matchResult.matchId = item.getLong("match-id");
//            matchResult.orderId = item.getLong("order-id");
//            matchResult.price = item.getDecimal("price");
//            matchResult.source = OrderSource::lookup(item.getString("source"));
//            matchResult.symbol = item.getString("symbol");
//            matchResult.type = OrderType::lookup(item.getString("type"));
//            matchResult.role = DealRole::lookup(item.getString("role"));
//            matchResult.filled_points = item.getDecimal("filled-points");
//            matchResult.fee_deduct_currency = item.getString("fee-deduct-currency");
//            return matchResult;
//        }
//    };
//
//}
//
//
//#endif /* MATCHRESULT_H */
//
