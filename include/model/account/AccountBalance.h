/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AccountBalance.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月23日, 上午12:12
 */

#ifndef ACCOUNTBALANCE_H
#define ACCOUNTBALANCE_H

#include "constant/enums.h"
#include "Balance.h"
#include <vector>

namespace Huobi {

    struct AccountBalance {
        long id;
        std::string subType;
        AccountType type;
        AccountState state;
        std::vector<Balance> list;
    };

}

#endif /* ACCOUNTBALANCE_H */

