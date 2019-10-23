/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AccountBalanceParser.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月23日, 上午10:45
 */

#ifndef ACCOUNTBALANCEPARSER_H
#define ACCOUNTBALANCEPARSER_H
#include "model/account/AccountBalance.h"
#include "../../../Utils/JsonWrapper.h"
#include "BalanceParser.h"

namespace Huobi {

    class AccountBalanceParser {
    public:

        static std::vector<AccountBalance> parseArray(JsonWrapper& json) {

            std::vector<AccountBalance> accountsBalance;
            for (int i = 0; i < json.size(); i++) {
                JsonWrapper item = json.getJsonObjectAt(i);
                AccountBalance accountBalance = parse(item);
                accountsBalance.push_back(accountBalance);
            }

            return accountsBalance;
        }

        static AccountBalance parse(JsonWrapper& json) {

            AccountBalance accountBalance;
            accountBalance.id = json.getLong("id");
            accountBalance.type = AccountType::lookup(json.getString("type"));
            accountBalance.state = AccountState::lookup(json.getString("state"));
            accountBalance.subType = json.getString("symbol");
            JsonWrapper list = json.getJsonObjectOrArray("list");
            accountBalance.list = BalanceParser::parseArray(list);
            return accountBalance;
        }

    };

}

#endif /* ACCOUNTBALANCEPARSER_H */

