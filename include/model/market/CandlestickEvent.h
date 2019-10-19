/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CandlestickEvent.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月18日, 上午10:17
 */

#ifndef CANDLESTICKEVENT_H
#define CANDLESTICKEVENT_H
#include "Candlestick.h"
namespace Huobi {

    /**
     * The candlestick/kline data.
     */
    struct CandlestickEvent {
        
        std::string ch;
        long ts;
        Candlestick candlestick;

    };
}

#endif /* CANDLESTICKEVENT_H */

