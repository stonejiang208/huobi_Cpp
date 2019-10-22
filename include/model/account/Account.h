/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Account.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月15日, 下午7:27
 */

#ifndef ACCOUNT_H
#define ACCOUNT_H


#include <vector>
#include "constant/enums.h"
#include "constant/Decimal.h"
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

        std::string subtype;


    };
}


#endif /* ACCOUNT_H */

