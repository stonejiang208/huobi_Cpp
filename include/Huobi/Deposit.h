//#ifndef DEPOSIT_H
//#define DEPOSIT_H
//
//#include <string>
//#include "Huobi/Decimal.h"
//#include "Huobi/Enums.h"
//
//namespace Huobi {
//
//    /**
//     * The latest status for deposits.
//     */
//    struct Deposit {
//        /**
//         * The transfer id.
//         */
//        long id = 0;
//
//        /**
//         * The crypto currency to deposit.
//         */
//        std::string currency;
//
//        /**
//         * The on-chain transaction hash.
//         */
//        std::string txHash;
//
//        /**
//         * The number of crypto asset transferred in its minimum unit.
//         */
//        Decimal amount;
//
//        /**
//         * The deposit source address.
//         */
//        std::string address;
//
//        /**
//         * The user defined address tag.
//         */
//        std::string addressTag;
//
//        /**
//         * The amount of fee taken by Huobi in this crypto's minimum unit.
//         */
//        Decimal fee;
//
//        /**
//         * The UNIX formatted timestamp in UTC for the transfer creation.
//         */
//        long createdTimestamp = 0;
//
//        /**
//         * The UNIX formatted timestamp in UTC for the transfer's latest update.
//         */
//        long updatedTimestamp = 0;
//
//        /**
//         * The deposit state of this transfer.
//         */
//        DepositState depositState;
//
//        static RestApiJsonParser<std::vector<Deposit> > getDataParser() {
//            RestApiJsonParser<std::vector < Deposit>> res;
//            res.parseJson = [](JsonWrapper json) {
//                std::vector<Deposit> lstdeposit;
//                JsonWrapper data = json.getJsonObjectOrArray("data");
//                for (int i = 0; i < data.size(); i++) {
//                    JsonWrapper item = data.getJsonObjectAt(i);
//                    Deposit deposit = parse(item);
//                    lstdeposit.push_back(deposit);
//                }
//                return lstdeposit;
//            };
//            return res;
//        }
//
//        static Deposit parse(JsonWrapper item) {
//            Deposit deposit;
//            deposit.id = item.getLong("id");
//            deposit.currency = item.getString("currency");
//            deposit.txHash = item.getString("tx-hash");
//            deposit.amount = item.getDecimal("amount");
//            deposit.address = item.getString("address");
//            deposit.addressTag = item.getString("address-tag");
//            deposit.fee = item.getDecimal("fee");
//            deposit.depositState = DepositState::lookup(item.getString("state"));
//            deposit.createdTimestamp =
//                    TimeService::convertCSTInMillisecondToUTC(item.getLong("created-at"));
//            deposit.updatedTimestamp =
//                    TimeService::convertCSTInMillisecondToUTC(item.getLong("updated-at"));
//            return deposit;
//        }
//
//    };
//
//}
//
//#endif /* DEPOSIT_H */
//
