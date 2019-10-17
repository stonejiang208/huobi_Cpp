//#ifndef MARGINBALANCEDETAIL_H
//#define MARGINBALANCEDETAIL_H
//
//#include <string>
//#include <vector>
//
//#include "Huobi/Enums.h"
//#include "Huobi/Decimal.h"
//#include "Huobi/Balance.h"
//
//namespace Huobi {
//
//    struct MarginBalanceDetail {
//        /**
//         * The id of margin account.
//         */
//        long id = 0;
//
//        /**
//         * The margin loan pair, e.g. btcusdt, bccbtc
//         */
//        std::string symbol;
//
//        /**
//         * The loan state.
//         */
//        AccountState state;
//        AccountType type;
//
//        /**
//         * The risk rate
//         */
//        Decimal riskRate;
//
//        /**
//         * The price which triggers closeout.
//         */
//        Decimal flPrice;
//        std::string flType;
//
//        /**
//         * The list of margin accounts and their details.
//         */
//        std::vector<Balance> subAccountBalance;
//       
//        static RestApiJsonParser<std::vector<MarginBalanceDetail> > getDataParser() {
//            RestApiJsonParser<std::vector < MarginBalanceDetail>> res;
//            res.parseJson = [](JsonWrapper json) {
//                std::vector<MarginBalanceDetail> marginBalanceDetailList;
//                JsonWrapper dataArray = json.getJsonObjectOrArray("data");
//                for (int i = 0; i < dataArray.size(); i++) {
//                    JsonWrapper itemInData = dataArray.getJsonObjectAt(i);
//                    MarginBalanceDetail marginBalanceDetail;
//                    marginBalanceDetail.id = itemInData.getLong("id");
//                    marginBalanceDetail.type = AccountType::lookup(itemInData.getString("type"));
//                    marginBalanceDetail.symbol = itemInData.getString("symbol");
//                    marginBalanceDetail.flPrice = itemInData.getDecimal("fl-price");
//                    marginBalanceDetail.flType = itemInData.getString("fl-type");
//                    marginBalanceDetail.state = AccountState::lookup(itemInData.getString("state"));
//                    marginBalanceDetail.riskRate = itemInData.getDecimal("risk-rate");
//                    JsonWrapper listArray = itemInData.getJsonObjectOrArray("list");
//                    for (int i = 0; i < listArray.size(); i++) {
//                        JsonWrapper itemInList = listArray.getJsonObjectAt(i);
//                        Balance balance;
//                        balance.currency = itemInList.getString("currency");
//                        balance.type = BalanceType::lookup(itemInList.getString("type"));
//                        balance.balance = itemInList.getDecimal("balance");
//                        marginBalanceDetail.subAccountBalance.push_back(balance);
//                    }
//                    marginBalanceDetailList.push_back(marginBalanceDetail);
//                }
//                return marginBalanceDetailList;
//            };
//            return res;
//        }
//
//        static MarginBalanceDetail parse(JsonWrapper itemInData) {
//            MarginBalanceDetail marginBalanceDetail;
//            marginBalanceDetail.id = itemInData.getLong("id");
//            marginBalanceDetail.type = AccountType::lookup(itemInData.getString("type"));
//            marginBalanceDetail.symbol = itemInData.getString("symbol");
//            marginBalanceDetail.flPrice = itemInData.getDecimal("fl-price");
//            marginBalanceDetail.flType = itemInData.getString("fl-type");
//            marginBalanceDetail.state = AccountState::lookup(itemInData.getString("state"));
//            marginBalanceDetail.riskRate = itemInData.getDecimal("risk-rate");
//            marginBalanceDetail.subAccountBalance = Balance::getParser("list").parseJson(itemInData);
//            return marginBalanceDetail;
//        }
//
//    };
//}
//
//
//#endif /* MARGINBALANCEDETAIL_H */
//
