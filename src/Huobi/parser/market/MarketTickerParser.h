/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MarketTickerParser.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月22日, 下午2:16
 */

#ifndef MARKETTICKERPARSER_H
#define MARKETTICKERPARSER_H

#include "model/market/MarketTicker.h"
#include "../../../Utils/JsonDocument.h"
#include "../../../Utils/JsonWrapper.h"
namespace Huobi {

    class MarketTickerParser {
    public:

        static std::vector<MarketTicker> parseArray(JsonWrapper& json) {
            std::vector<MarketTicker> marketTickerVec;
            
            for (int i = 0; i < json.size(); i++) {
                JsonWrapper item = json.getJsonObjectAt(i);
                MarketTicker marketTicker = parse(item);
                marketTickerVec.push_back(marketTicker);
            }
            return marketTickerVec;
        }

        static MarketTicker parse(JsonWrapper& json) {
            MarketTicker marketTicker;
            marketTicker.amount = json.getDecimal("amount");
            marketTicker.open = json.getDecimal("open");
            marketTicker.close = json.getDecimal("close");
            marketTicker.high = json.getDecimal("high");
            marketTicker.low = json.getDecimal("low");
            marketTicker.count = json.getLong("count");
            marketTicker.vol = json.getDecimal("vol");
            marketTicker.symbol = json.getString("symbol");
            return marketTicker;
        }
    };

}

#endif /* MARKETTICKERPARSER_H */

