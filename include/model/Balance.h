/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Balance.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月15日, 下午7:45
 */

#ifndef BALANCE_H
#define BALANCE_H


#include <string>
#include <vector>
#include "constant/enums.h"
#include "constant/Decimal.h"
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

        
    };

}


#endif /* BALANCE_H */

