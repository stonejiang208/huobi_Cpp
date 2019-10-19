/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SubCandlestickRequest.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月17日, 下午7:09
 */

#ifndef SUBCANDLESTICKREQUEST_H
#define SUBCANDLESTICKREQUEST_H
#include "constant/enums.h"
namespace Huobi {

    struct SubCandlestickRequest {

        SubCandlestickRequest(
                const std::string& symbol,
                const CandlestickInterval& interval) : symbol(symbol), interval(interval) {
        }

        std::string symbol;
        CandlestickInterval interval;

    };

}

#endif /* SUBCANDLESTICKREQUEST_H */

