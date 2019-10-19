/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Candlestick.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月16日, 下午4:44
 */

#ifndef CANDLESTICK_H
#define CANDLESTICK_H


#include <vector>
#include "constant/Decimal.h"

namespace Huobi {

    /**
     * The candlestick/kline data.
     */
    struct Candlestick {
      
        /**
         * The query id.
         */
        long id =0;

        /**
         * The aggregated trading volume in USDT.
         */
        Decimal amount;

        /**
         * The number of completed trades. it returns 0 when get ETF candlestick.
         */
        long count = 0;

        /**
         * The opening price.
         */
        Decimal open;

        /**
         * The closing price.
         */
        Decimal close;

        /**
         * The low price.
         */
        Decimal low;

        /**
         * The high price.
         */
        Decimal high;

        /**
         * The trading volume in base currency.
         */
        Decimal volume;

        

    };
}



#endif /* CANDLESTICK_H */

