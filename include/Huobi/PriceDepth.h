//#ifndef PRICEDEPTH_H
//#define PRICEDEPTH_H
//
//#include<vector>
//#include "DepthEntry.h"
//namespace Huobi {
//
//    /**
//     * The price depth information.
//     */
//    struct PriceDepth {
//        /**
//         * The UNIX formatted timestamp in UTC.
//         */
//        long timestamp;
//
//        /**
//         * The list of the bid depth. The content is DepthEntry class.
//         */
//        std::vector<DepthEntry> bids;
//
//        /**
//         * The list of the ask depth. The content is DepthEntry class.
//         */
//        std::vector<DepthEntry> asks;
//
//        static RestApiJsonParser<PriceDepth > getTickParser(int size) {
//            RestApiJsonParser<PriceDepth> res;
//            res.parseJson = [size](JsonWrapper json) {
//                PriceDepth price = parse(json, size);
//                return price;
//            };
//            return res;
//        }
//
//        static PriceDepth parse(JsonWrapper json, int size) {
//            PriceDepth price;
//            JsonWrapper tick = json.getJsonObjectOrArray("tick");
//            long ts = TimeService::convertCSTInMillisecondToUTC(tick.getLong("ts"));
//            JsonWrapper bids = tick.getJsonObjectOrArray("bids");
//            JsonWrapper asks = tick.getJsonObjectOrArray("asks");
//            std::vector<DepthEntry> bidList;
//            std::vector<DepthEntry> askList;
//            for (int i = 0; i < size; i++) {
//                JsonWrapper bidEntry = bids.getArrayAt(i);
//                DepthEntry entry;
//                entry.price = bidEntry.getDecimalAt(0);
//                entry.amount = bidEntry.getDecimalAt(1);
//                bidList.push_back(entry);
//            }
//            for (int i = 0; i < size; i++) {
//                JsonWrapper askEntry = asks.getArrayAt(i);
//                DepthEntry entry;
//                entry.price = askEntry.getDecimalAt(0);
//                entry.amount = askEntry.getDecimalAt(1);
//                askList.push_back(entry);
//            }
//            price.bids = bidList;
//            price.asks = askList;
//            price.timestamp = ts;
//            return price;
//        }
//    };
//}
//#endif /* PRICEDEPTH_H */
//
