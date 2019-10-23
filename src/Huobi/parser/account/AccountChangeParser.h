/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AccountChangeParser.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月23日, 下午7:06
 */

#ifndef ACCOUNTCHANGEPARSER_H
#define ACCOUNTCHANGEPARSER_H

namespace Huobi {

    class AccountChangeParser {
    public:

        static std::vector<AccountChange> parseArray(JsonWrapper& json) {

            std::vector<AccountChange> accountChangeVec;
            for (int i = 0; i < json.size(); i++) {
                JsonWrapper item = json.getJsonObjectAt(i);
                AccountChange accountChange = parse(item);
                accountChangeVec.push_back(accountChange);
            }

            return accountChangeVec;
        }

        static AccountChange parse(JsonWrapper& item) {
            AccountChange accountChange;
            accountChange.accountId = item.getLong("id");
            accountChange.balance = item.getDecimal("balance");
            accountChange.type = BalanceType::lookup(item.getString("type"));
            accountChange.currency = item.getString("currency");
            return accountChange;
        }

    };

}

#endif /* ACCOUNTCHANGEPARSER_H */

