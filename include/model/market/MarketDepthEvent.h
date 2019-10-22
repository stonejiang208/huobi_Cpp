/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MarketDepthEvent.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月22日, 下午4:39
 */

#ifndef MARKETDEPTHEVENT_H
#define MARKETDEPTHEVENT_H

#include "MarketDepth.h"
namespace Huobi {

    /**
     * The candlestick/kline data.
     */
    struct MarketDepthEvent {
        
        std::string ch;
        long ts;
        MarketDepth depth;

    };
}

#endif /* MARKETDEPTHEVENT_H */

