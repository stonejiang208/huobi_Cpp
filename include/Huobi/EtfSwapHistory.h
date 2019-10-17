//#ifndef ETFSWAPHISTORY_H
//#define ETFSWAPHISTORY_H
//
//#include <string>
//#include <vector>
//#include "Huobi/UnitPrice.h"
//#include "Huobi/Enums.h"
//#include "Huobi/Decimal.h"
//
//namespace Huobi {
//
//    /*
//     * The past creation and redemption.
//
//    :member
//        created_timestamp: 
//        currency: 
//        amount: 
//        type: 
//        status: 
//        rate: 
//        fee: 
//
//        point_card_amount: 
//        used_currency_list: 
//        obtain_currency_list: For creation this is the amount for ETF created.
//            
//     */
//    struct EtfSwapHistory {
//        /**
//         * The UNIX formatted timestamp in UTC of the operation.
//         */
//        long createdTimestamp = 0;
//
//        /**
//         * The ETF name.
//         */
//        std::string currency;
//
//        /**
//         * Creation or redemption amount.
//         */
//        Decimal amount;
//
//        /**
//         * The swap type. Creation or redemption.
//         */
//        EtfSwapType type;
//
//        /**
//         * The operation result.
//         */
//        int status = 0;
//
//        /**
//         * The fee rate.
//         */
//        Decimal rate;
//
//        /**
//         * The actual fee amount.
//         */
//        Decimal fee;
//
//        /**
//         * Discount from point card.
//         */
//        Decimal pointCardAmount;
//
//        /**
//         * For creation this is the list and amount of underlying assets used for ETF creation.
//         * For redemption this is the amount of ETF used for redemption. The content is UnitPrice class.
//         */
//        std::vector<UnitPrice> usedCurrencyList;
//
//        /**
//         * For redemption this is the list and amount of underlying assets obtained. The content is UnitPrice class.
//         */
//        std::vector<UnitPrice> obtainCurrencyList;
//
//        static RestApiJsonParser<std::vector<EtfSwapHistory> > getDataParser() {
//            RestApiJsonParser<std::vector < EtfSwapHistory>> res;
//            res.parseJson = [](JsonWrapper json) {
//                std::vector<EtfSwapHistory> etfSwapHistoryList;
//                JsonWrapper data = json.getJsonObjectOrArray("data");
//                for (int i = 0; i < data.size(); i++) {
//                    JsonWrapper item = data.getJsonObjectAt(i);
//                    EtfSwapHistory etfSwapHistory = parse(item);
//                    etfSwapHistoryList.push_back(etfSwapHistory);
//                }
//                return etfSwapHistoryList;
//            };
//            return res;
//        }
//
//        static EtfSwapHistory parse(JsonWrapper item) {
//            EtfSwapHistory etfSwapHistory;
//            etfSwapHistory.createdTimestamp = item.getLong("gmt_created");
//            etfSwapHistory.currency = item.getString("currency");
//            etfSwapHistory.amount = (item.getDecimal("amount"));
//            etfSwapHistory.type = EtfSwapType::lookup(item.getString("type"));
//            etfSwapHistory.status = item.getInt("status");
//            JsonWrapper detail = item.getJsonObjectOrArray("detail");
//            etfSwapHistory.rate = detail.getDecimal("rate");
//            etfSwapHistory.fee = detail.getDecimal("fee");
//            etfSwapHistory.pointCardAmount = detail.getDecimal("point_card_amount");          
//            etfSwapHistory.usedCurrencyList = UnitPrice::getParser("used_currency_list").parseJson(detail);            
//            etfSwapHistory.obtainCurrencyList = UnitPrice::getParser("obtain_currency_list").parseJson(detail);
//            return etfSwapHistory;
//        }
//
//    };
//
//}
//
//#endif /* ETFSWAPHISTORY_H */
//
