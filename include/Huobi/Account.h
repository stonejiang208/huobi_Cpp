#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <vector>
#include "Huobi/Enums.h"
#include "Huobi/Balance.h"
#include "/root/huobi_Cpp/src/TimeService.h"
#include "/root/huobi_Cpp/src/RestApiJsonParser.h"
#include "/root/huobi_Cpp/src/Utils/JsonWrapper.h"
#include "Huobi/Decimal.h"
namespace Huobi {

    /**
     * The account information for spot account, margin account etc.
     */
    struct Account {
        /**
         * The unique account id.
         */
        long id = 0;

        /*
         * The type of this account, possible value: spot, margin, otc, point.
         */
        AccountType type;

        /*
         * The account state, possible value: working, lock.
         */
        AccountState state;

        /*
         * The balance list of the specified currency. The content is Balance class.
         */
        std::vector<Balance> balances;

        std::vector<Balance> getBalance(const char* currency) {
            std::vector<Balance> result;
            for (Balance balance : balances) {
                if (currency == balance.currency) {
                    result.push_back(balance);
                }
            }
            return result;
        }


        static RestApiJsonParser<std::vector<Account> > getDataParser() {
            RestApiJsonParser<std::vector < Account>> res;
            res.parseJson = [](JsonWrapper json) {
                std::vector<Account>accounts;
                JsonWrapper data = json.getJsonObjectOrArray("data");
                size_t size = data.size();
                for (int i = 0; i < size; i++) {
                    JsonWrapper item = data.getJsonObjectAt(i);
                    Account account = parse(item);
                    accounts.push_back(account);
                }
                return accounts;
            };
            return res;
        }

        static Account parse(JsonWrapper item) {
            Account account;
            account.id = item.getLong("id");
            account.type = AccountType::lookup(item.getString("type"));
            account.state = AccountState::lookup(item.getString("state"));
            return account;
        }

    };
}

#endif /* ACCOUNT_H */



