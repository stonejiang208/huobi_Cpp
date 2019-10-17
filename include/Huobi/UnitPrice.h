//#ifndef UNITPRICE_H
//#define UNITPRICE_H
//
//#include "Huobi/Decimal.h"
//
//namespace Huobi {
//
//    struct UnitPrice {
//        std::string currency;
//        Decimal amount;
//
//        static RestApiJsonParser<std::vector<UnitPrice >> getParser(const char* field) {
//            RestApiJsonParser<std::vector < UnitPrice>> res;
//            res.parseJson = [field](JsonWrapper json) {
//                JsonWrapper unitPrices = json.getJsonObjectOrArray(field);
//                std::vector<UnitPrice> unitPriceList;
//                for (int i = 0; i < unitPrices.size(); i++) {
//                    JsonWrapper item = unitPrices.getJsonObjectAt(i);
//                    UnitPrice unitPrice = parse(item);
//                    unitPriceList.push_back(unitPrice);
//                }
//                return unitPriceList;
//            };
//            return res;
//        }
//
//        static UnitPrice parse(JsonWrapper item) {
//            UnitPrice unitPrice;
//            unitPrice.currency = item.getString("currency");
//            unitPrice.amount = item.getDecimal("amount");
//            return unitPrice;
//        }
//    };
//}
//#endif /* UNITPRICE_H */
//
