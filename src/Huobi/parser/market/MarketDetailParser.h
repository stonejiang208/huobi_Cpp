/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MarketDetailParser.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月22日, 上午11:59
 */

#ifndef MARKETDETAILPARSER_H
#define MARKETDETAILPARSER_H

#include "model/market/MarketDetail.h"

namespace Huobi {

    class MarketDetailParser {
    public:

        static MarketDetail parse(JsonWrapper json) {
            MarketDetail marketDetail;
            marketDetail.id = json.getLong("id");
            marketDetail.amount = json.getDecimal("amount");
            marketDetail.open = json.getDecimal("open");
            marketDetail.close = json.getDecimal("close");
            marketDetail.high = json.getDecimal("high");
            marketDetail.low = json.getDecimal("low");
            marketDetail.count = json.getLong("count");
            marketDetail.vol = json.getDecimal("vol");
            return marketDetail;
        }
    };

}
#endif /* MARKETDETAILPARSER_H */

