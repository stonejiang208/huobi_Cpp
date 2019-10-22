/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MarketBBOEvent.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月22日, 下午5:23
 */

#ifndef MARKETBBOEVENT_H
#define MARKETBBOEVENT_H

#include "MarketBBO.h"
namespace Huobi {

    /**
     * The candlestick/kline data.
     */
    struct MarketBBOEvent {
        
        std::string ch;
        long ts;
        MarketBBO bbo;

    };
}

#endif /* MARKETBBOEVENT_H */

