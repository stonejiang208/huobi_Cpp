/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Balance.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月23日, 上午12:14
 */

#ifndef BALANCE_H
#define BALANCE_H
#include "constant/enums.h"
#include "constant/Decimal.h"
namespace Huobi {

    struct Balance {
        std::string currency;
        BalanceType type;
        Decimal balance;

    };

}

#endif /* BALANCE_H */

