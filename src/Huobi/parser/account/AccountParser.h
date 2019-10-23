/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AccountParser.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月22日, 下午7:23
 */

#ifndef ACCOUNTPARSER_H
#define ACCOUNTPARSER_H
#include "model/account/Account.h"
#include "../../../Utils/JsonWrapper.h"
#include <vector>
namespace Huobi {

    class AccountParser {
    public:

        static std::vector<Account> parseArray(JsonWrapper& json) {

            std::vector<Account> accountVec;
            for (int i = 0; i < json.size(); i++) {
                JsonWrapper item = json.getJsonObjectAt(i);
                Account account = parse(item);
                accountVec.push_back(account);
            }

            return accountVec;
        }

        static Account parse(JsonWrapper& item) {
            Account account;
            account.id = item.getLong("id");
            account.subtype = item.getString("subtype");
            account.type = AccountType::lookup(item.getString("type"));
            account.state = AccountState::lookup(item.getString("state"));
            return account;
        }

    };

}


#endif /* ACCOUNTPARSER_H */

