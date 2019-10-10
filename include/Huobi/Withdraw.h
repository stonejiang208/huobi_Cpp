#ifndef WITHDRAW_H
#define WITHDRAW_H

#include "Huobi/Enums.h"

namespace Huobi {

    /**
     * The latest status for withdraws.
     */
    struct Withdraw {
        /**
         * The transfer id.
         */
        long id;

        /**
         * The crypto currency to deposit.
         */
        std::string currency;

        /**
         * The on-chain transaction hash.
         */
        std::string txHash;

        /**
         * The number of crypto asset transferred in its minimum unit.
         */
        Decimal amount;

        /**
         * The deposit source address.
         */
        std::string address;

        /**
         * The user defined address tag.
         */
        std::string addressTag;

        /**
         * The amount of fee taken by Huobi in this crypto's minimum unit.
         */
        Decimal fee;

        /**
         * The UNIX formatted timestamp in UTC for the transfer creation.
         */
        long createdTimestamp;

        /**
         * The UNIX formatted timestamp in UTC for the transfer's latest update.
         */
        long updatedTimestamp;

        /**
         * The withdraw state of this transfer.
         */
        WithdrawState withdrawState;

  

        static RestApiJsonParser<std::vector<Withdraw> > getDataParser() {

            RestApiJsonParser<std::vector < Withdraw>> res;
            res.parseJson = [](JsonWrapper json) {
                std::vector<Withdraw> withdraws;
                JsonWrapper data = json.getJsonObjectOrArray("data");
                for (int i = 0; i < data.size(); i++) {
                    JsonWrapper item = data.getJsonObjectAt(i);
                    Withdraw withdraw = parse(item);
                    withdraws.push_back(withdraw);
                }
                return withdraws;
            };
            return res;
        }

        static Withdraw parse(JsonWrapper item) {
            Withdraw withdraw;
            withdraw.id = item.getLong("id");
            withdraw.currency = item.getString("currency");
            withdraw.txHash = item.getString("tx-hash");
            withdraw.amount = item.getDecimal("amount");
            withdraw.address = item.getString("address");
            withdraw.addressTag = item.getString("address-tag");
            withdraw.fee = item.getDecimal("fee");
            withdraw.withdrawState = WithdrawState::lookup(item.getString("state"));
            withdraw.createdTimestamp =
                    TimeService::convertCSTInMillisecondToUTC(item.getLong("created-at"));
            withdraw.updatedTimestamp =
                    TimeService::convertCSTInMillisecondToUTC(item.getLong("updated-at"));
            return withdraw;
        }
    };

}
#endif /* WITHDRAW_H */

