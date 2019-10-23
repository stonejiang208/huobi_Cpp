/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AccountChange.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月23日, 上午12:33
 */

#ifndef ACCOUNTCHANGE_H
#define ACCOUNTCHANGE_H

namespace Huobi {

    struct AccountChange {
        long accountId;
        std::string currency;
        BalanceType type;
        Decimal balance;

    };

}

#endif /* ACCOUNTCHANGE_H */

