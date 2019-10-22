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
                 printf("parse account\n");
                Account account = parse(item);
                 printf("after parse account\n");
                accountVec.push_back(account);
            }

            return accountVec;
        }

        static Account parse(JsonWrapper& item) {
            Account account;
           
            account.id = item.getLong("id");
           
            std::cout<<item.getString("state")<<std::endl;
            
            std::cout<<"subtype:"<<std::endl;
            account.subtype = item.getString("subtype");
           
              std::cout<<"type:"<<std::endl;
           account.type = AccountType::lookup(item.getString("type"));
           std::cout<<"state:"<<std::endl;
            account.state = AccountState::lookup(item.getString("state"));
            
           
            
         //   account.type = AccountType::lookup(item.getString("type"));
            
            
            
            
            return account;
        }

    };

}


#endif /* ACCOUNTPARSER_H */

