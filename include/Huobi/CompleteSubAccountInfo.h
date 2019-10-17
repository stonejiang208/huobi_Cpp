//#ifndef COMPLETESUBACCOUNTINFO_H
//#define COMPLETESUBACCOUNTINFO_H
//
//#include <vector>
//#include "Huobi/Enums.h"
//
//namespace Huobi {
//
//    /**
//     *  Sub-account completed info
//     */
//    struct CompleteSubAccountInfo {
//        /**
//         * The sub-id.
//         */
//        long id = 0;
//
//        /**
//         * The sub account type.
//         */
//        AccountType type;
//
//        /**
//         * The balance list, the content is Balance class.
//         */
//        std::vector<Balance> balances;
//
//        static RestApiJsonParser<std::vector<CompleteSubAccountInfo> > getDataParser() {
//
//            RestApiJsonParser<std::vector < CompleteSubAccountInfo>> res;
//            res.parseJson = [](JsonWrapper json) {
//                std::vector<CompleteSubAccountInfo> completeSubAccountInfos;
//                JsonWrapper data = json.getJsonObjectOrArray("data");
//                for (int i = 0; i < data.size(); i++) {
//                    JsonWrapper item = data.getJsonObjectAt(i);
//                    CompleteSubAccountInfo completeSubAccountInfo = parse(item);
//                    completeSubAccountInfos.push_back(completeSubAccountInfo);
//                }
//                return completeSubAccountInfos;
//            };
//            return res;
//        }
//
//        static CompleteSubAccountInfo parse(JsonWrapper item) {
//            CompleteSubAccountInfo completeSubAccountInfo;
//            completeSubAccountInfo.id = item.getLong("id");
//            completeSubAccountInfo.type = AccountType::lookup(item.getString("type"));
//            std::vector<Balance> balances = Balance::getParser("list").parseJson(item);
//            completeSubAccountInfo.balances = balances;
//            return completeSubAccountInfo;
//        }
//    };
//
//}
//
//
//#endif /* COMPLETESUBACCOUNTINFO_H */
//
