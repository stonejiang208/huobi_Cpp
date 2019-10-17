//#ifndef SYMBOLS_H
//#define SYMBOLS_H
//
//#include <string>
//#include "/root/huobi_Cpp/src/TimeService.h"
//#include "/root/huobi_Cpp/src/RestApiJsonParser.h"
//#include "/root/huobi_Cpp/src/Utils/JsonWrapper.h"
//#include <vector>
//namespace Huobi {
//
//    /**
//     * The Huobi supported symbols.
//     */
//    struct Symbols {
//        /**
//         * The base currency in a trading symbol.
//         */
//        std::string baseCurrency;
//
//        /**
//         * The quote currency in a trading symbol.
//         */
//        std::string quoteCurrency;
//
//        /**
//         * The quote currency precision when quote price (decimal places).
//         */
//        int pricePrecision;
//
//        /**
//         * The base currency precision when quote amount (decimal places).
//         */
//        int amountPrecision;
//
//        /**
//         * The trading section, possible values: [main，innovation，bifurcation].
//         */
//        std::string symbolPartition;
//
//        /**
//         * The symbol, like "btcusdt".
//         */
//        std::string symbol;
//        /**
//         * The symbol state ,possible values: [online，offline,suspend].
//         */
//        SymbolState state;
//
//        /**
//         * The value precision
//         */
//        int valuePrecision;
//
//        /**
//         * The min order amount
//         */
//        long minOrderAmt;
//
//        /**
//         * The max order amount
//         */
//        long maxOrderAmt;
//
//        /**
//         * The min order value
//         */
//        long minOrderValue;
//
//        /**
//         * The leverage ratio
//         */
//        int leverageRatio;
//
//        static RestApiJsonParser<std::vector<Symbols> > getDataParser() {
//            RestApiJsonParser<std::vector < Symbols>> res;
//            res.parseJson = [](JsonWrapper json) {
//                std::vector<Symbols> symbolsList;
//                JsonWrapper data = json.getJsonObjectOrArray("data");
//                for (int i = 0; i < data.size(); i++) {
//                    JsonWrapper item = data.getJsonObjectAt(i);
//                    Symbols symbols = parse(item);
//                    symbolsList.push_back(symbols);
//                }
//                return symbolsList;
//            };
//            return res;
//        }
//
//        static Symbols parse(JsonWrapper item) {
//            Symbols symbols;
//            symbols.baseCurrency = item.getString("base-currency");
//            symbols.quoteCurrency = item.getString("quote-currency");
//            symbols.pricePrecision = item.getInt("price-precision");
//            symbols.amountPrecision = item.getInt("amount-precision");
//            symbols.symbolPartition = item.getString("symbol-partition");
//            symbols.symbol = item.getString("symbol");
//            symbols.state = SymbolState::lookup(item.getString("state"));
//            symbols.valuePrecision = item.getInt("value-precision");
//            symbols.minOrderAmt = item.getLong("min-order-amt");
//            symbols.maxOrderAmt = item.getLong("max-order-amt");
//            symbols.leverageRatio = item.getIntOrDefault("leverage-ratio", 0);
//            return symbols;
//        }
//
//
//    };
//
//
//}
//
//
//#endif /* SYMBOLS_H */
//
