//#ifndef CANDLESTICK_H
//#define CANDLESTICK_H
//
//#include "Huobi/Decimal.h"
//#include "/root/huobi_Cpp/src/TimeService.h"
//#include "/root/huobi_Cpp/src/RestApiJsonParser.h"
//#include "/root/huobi_Cpp/src/Utils/JsonWrapper.h"
//#include <vector>
//
//namespace Huobi {
//
//    /**
//     * The candlestick/kline data.
//     */
//    struct Candlestick {
//        /**
//         * The UNIX formatted timestamp in UTC.
//         */
//        long timestamp = 0;
//
//        /**
//         * The aggregated trading volume in USDT.
//         */
//        Decimal amount;
//
//        /**
//         * The number of completed trades. it returns 0 when get ETF candlestick.
//         */
//        long count = 0;
//
//        /**
//         * The opening price.
//         */
//        Decimal open;
//
//        /**
//         * The closing price.
//         */
//        Decimal close;
//
//        /**
//         * The low price.
//         */
//        Decimal low;
//
//        /**
//         * The high price.
//         */
//        Decimal high;
//
//        /**
//         * The trading volume in base currency.
//         */
//        Decimal volume;
//
//        /**
//         * The query id.
//         */
//        long id = 0;
//
//        static RestApiJsonParser<std::vector<Candlestick> > getDataParser() {
//            RestApiJsonParser<std::vector < Candlestick>> res;
//            res.parseJson = [](JsonWrapper json) {
//                std::vector<Candlestick> cans;
//                JsonWrapper data = json.getJsonObjectOrArray("data");
//                for (int i = 0; i < data.size(); i++) {
//                    JsonWrapper item = data.getJsonObjectAt(i);
//                    Candlestick candlestick = parse(item);
//                    cans.push_back(candlestick);
//                }
//                return cans;
//            };
//            return res;
//        }
//
//        static Candlestick parse(JsonWrapper item) {
//            Candlestick candlestick;
//            candlestick.timestamp =
//                    TimeService::convertCSTInSecondToUTC(item.getLong("id"));
//            candlestick.id = item.getLong("id");
//            candlestick.open = item.getDecimal("open");
//            candlestick.close = item.getDecimal("close");
//            candlestick.low = item.getDecimal("low");
//            candlestick.high = item.getDecimal("high");
//            candlestick.amount = item.getDecimal("amount");
//            candlestick.count = item.getLongOrDefault("count",0);
//            candlestick.volume = item.getDecimal("vol");
//            return candlestick;
//        }
//    };
//}
//
//#endif /* CANDLESTICK_H */
//
