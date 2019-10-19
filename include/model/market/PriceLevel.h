/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PriceLevel.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月17日, 下午4:33
 */

#ifndef PRICELEVEL_H
#define PRICELEVEL_H
#include "constant/Decimal.h"
namespace Huobi {

    struct PriceLevel {
        Decimal price;
        Decimal amount;

    };
}


#endif /* PRICELEVEL_H */

