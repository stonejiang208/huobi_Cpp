/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MarketBBOParser.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月22日, 下午5:30
 */

#ifndef MARKETBBOPARSER_H
#define MARKETBBOPARSER_H

namespace Huobi {

    class MarketBBOParser {
    public:
        static MarketBBO parse(JsonWrapper& item) {
            MarketBBO bbo;
            bbo.symbol = item.getString("symbol");
            bbo.ask = item.getDecimal("ask");
            bbo.askSize = item.getDecimal("askSize");
            bbo.bid = item.getDecimal("bid");
            bbo.bidSize = item.getDecimal("bidSize");
            bbo.quoteTime = item.getLong("quoteTime");
            return bbo;
        }
    };
}

#endif /* MARKETBBOPARSER_H */

