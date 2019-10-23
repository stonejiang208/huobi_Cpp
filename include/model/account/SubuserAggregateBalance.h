/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SubuserAggregateBalance.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月23日, 上午12:27
 */

#ifndef SUBUSERAGGREGATEBALANCE_H
#define SUBUSERAGGREGATEBALANCE_H

#include "constant/enums.h"
#include "constant/Decimal.h"
namespace Huobi {

    struct SubuserAggregateBalance {
        std::string currency;
        AccountType type;
        Decimal balance;

    };

}

#endif /* SUBUSERAGGREGATEBALANCE_H */

