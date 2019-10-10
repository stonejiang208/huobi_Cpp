#ifndef BALANCE_H
#define BALANCE_H

#include <string>
#include "Huobi/Enums.h"
#include "Huobi/Decimal.h"
#include "/root/huobi_Cpp/src/TimeService.h"
#include "/root/huobi_Cpp/src/RestApiJsonParser.h"
#include "/root/huobi_Cpp/src/Utils/JsonWrapper.h"
#include "Huobi/Decimal.h"
#include <vector>

namespace Huobi {

    /**
     * The balance of specified account.
     */
    struct Balance {
        /**
         * The currency of this balance.
         */
        std::string currency;

        /**
         * The balance type, trade or frozen.
         */
        BalanceType type;

        /**
         * The balance in the main currency unit.
         */
        Decimal balance;

        static RestApiJsonParser<std::vector<Balance> > getDataParser() {

            RestApiJsonParser<std::vector < Balance>> res;
            res.parseJson = [](JsonWrapper json) {
                std::vector<Balance> balances;
                JsonWrapper data = json.getJsonObjectOrArray("data");
                JsonWrapper list = data.getJsonObjectOrArray("list");
                for (int i = 0; i < list.size(); i++) {
                    JsonWrapper item = list.getJsonObjectAt(i);
                    Balance balance = parse(item);
                    balances.push_back(balance);
                }
                return balances;
            };
            return res;
        }

        static Balance parse(JsonWrapper item) {
            Balance balance;
            balance.balance = item.getDecimal("balance");
            balance.currency = item.getString("currency");
            balance.type = BalanceType::lookup(item.getString("type"));
            return balance;
        }
    };

}
#endif /* BALANCE_H */

