/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CandlestickRequest.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月16日, 下午3:27
 */

#ifndef CANDLESTICKREQUEST_H
#define CANDLESTICKREQUEST_H


#include <string>
#include "constant/enums.h"

namespace Huobi {

    /**
     * The request for getting candlestick/kline data.
     */
    struct CandlestickRequest {

        /**
         * The request for getting candlestick/kline data.
         *
         * \param symbol: The symbol, like "btcusdt". To query hb10, put "hb10" at here. (mandatory)
         * \param interval: The candlestick/kline interval, MIN1, MIN5, DAY1 etc. (mandatory)
         */

        CandlestickRequest(const std::string& symbol, const CandlestickInterval& interval) : symbol(symbol), interval(interval) {
        }

        /**
         * The request for getting candlestick/kline data.
         *
         * \param symbol: The symbol, like "btcusdt". To query hb10, put "hb10" at here. (mandatory)
         * \param interval: The candlestick/kline interval, MIN1, MIN5, DAY1 etc. (mandatory)
         * \param size: The maximum number of candlestick/kline requested. Range [1 - 2000] default 150. (optional) 
         */

        CandlestickRequest(
                const std::string& symbol,
                const CandlestickInterval& interval,
                int size) : symbol(symbol), interval(interval), size(size) {
        }

        std::string symbol;
        CandlestickInterval interval;
        int size = 0;
    };

}



#endif /* CANDLESTICKREQUEST_H */

