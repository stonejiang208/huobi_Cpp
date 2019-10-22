/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MarketBBO.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月22日, 下午5:24
 */

#ifndef MARKETBBO_H
#define MARKETBBO_H
#include "constant/Decimal.h"
namespace Huobi {

    struct MarketBBO {
        std::string symbol;
        long quoteTime;
        Decimal bid;
        Decimal bidSize;
        Decimal ask;
        Decimal askSize;
    };

}

#endif /* MARKETBBO_H */

