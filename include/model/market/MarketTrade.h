/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MarketTrade.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月22日, 下午3:19
 */

#ifndef MARKETTRADE_H
#define MARKETTRADE_H
#include "constant/Decimal.h"
#include "constant/enums.h"
namespace Huobi {

    struct MarketTrade {
        std::string id;
        long tradeId;
        Decimal price;
        Decimal amount;
        TradeDirection direction;
        long ts;
    };

}

#endif /* MARKETTRADE_H */

