/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BalanceParser.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月23日, 上午11:35
 */

#ifndef BALANCEPARSER_H
#define BALANCEPARSER_H
#include "../../../Utils/JsonWrapper.h"
#include "model/account/Balance.h"
namespace Huobi {

    class BalanceParser {
    public:

        static std::vector<Balance> parseArray(JsonWrapper& json) {

            std::vector<Balance> balanceVec;
            for (int i = 0; i < json.size(); i++) {
                JsonWrapper item = json.getJsonObjectAt(i);
                Balance balance = parse(item);
                balanceVec.push_back(balance);
            }

            return balanceVec;
        }

        static Balance parse(JsonWrapper& item) {
            Balance balance;
            balance.balance = item.getDecimal("balance");
            balance.currency = item.getString("currency");           
            balance.type= BalanceType::lookup(item.getString("type"));
            return balance;
        }

    };

}


#endif /* BALANCEPARSER_H */

