/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SubuserAggregateBalanceParser.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月23日, 下午5:22
 */

#ifndef SUBUSERAGGREGATEBALANCEPARSER_H
#define SUBUSERAGGREGATEBALANCEPARSER_H

#include "model/account/SubuserAggregateBalance.h"
#include "../../../Utils/JsonWrapper.h"
#include <vector>
namespace Huobi {

    class SubuserAggregateBalanceParser {
    public:

        static std::vector<SubuserAggregateBalance> parseArray(JsonWrapper& json) {

            std::vector<SubuserAggregateBalance> subuserAggregateBalances;
            for (int i = 0; i < json.size(); i++) {
                JsonWrapper item = json.getJsonObjectAt(i);
                SubuserAggregateBalance subuserAggregateBalance = parse(item);
                subuserAggregateBalances.push_back(subuserAggregateBalance);
            }

            return subuserAggregateBalances;
        }

        static SubuserAggregateBalance parse(JsonWrapper& item) {
            
            SubuserAggregateBalance subuserAggregateBalance;
            subuserAggregateBalance.currency = item.getString("currency");
            subuserAggregateBalance.type = AccountType::lookup(item.getString("type"));
            subuserAggregateBalance.balance = item.getDecimal("balance");
            return subuserAggregateBalance;
        }

    };

}

#endif /* SUBUSERAGGREGATEBALANCEPARSER_H */

