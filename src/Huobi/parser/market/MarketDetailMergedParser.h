/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MarketDetailMergedParser.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月17日, 下午4:58
 */

#ifndef MARKETDETAILMERGEDPARSER_H
#define MARKETDETAILMERGEDPARSER_H
#include "PriceLevelParser.h"
namespace Huobi {

    class MarketDetailMergedParser {
    public:

        static MarketDetailMerged parse(JsonWrapper& json) {
            MarketDetailMerged marketDetailMerged;
            marketDetailMerged.id = json.getLong("id");
            marketDetailMerged.amount = json.getDecimal("amount");
            marketDetailMerged.open = json.getDecimal("open");
            marketDetailMerged.close = json.getDecimal("close");
            marketDetailMerged.high = json.getDecimal("high");
            marketDetailMerged.low = json.getDecimal("low");
            marketDetailMerged.count = json.getLong("count");
            marketDetailMerged.vol = json.getDecimal("vol");
            JsonWrapper ask=json.getJsonObjectOrArray("ask");
            JsonWrapper bid=json.getJsonObjectOrArray("bid");
            marketDetailMerged.ask = PriceLevelParser::parse(ask);
            marketDetailMerged.bid = PriceLevelParser::parse(bid);

            return marketDetailMerged;
        }
    };

}

#endif /* MARKETDETAILMERGEDPARSER_H */

