/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MarketDepthParser.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月22日, 下午3:08
 */

#ifndef MARKETDEPTHPARSER_H
#define MARKETDEPTHPARSER_H
#include "model/market/MarketDepth.h"
#include "PriceLevelParser.h"
namespace Huobi {

    class MarketDepthParser {
    public:

        static MarketDepth parse(JsonWrapper json) {
            MarketDepth price;
            price.version = json.getLongOrDefault("version",0);
            price.ts = json.getLongOrDefault("ts",0);
            JsonWrapper bids = json.getJsonObjectOrArray("bids");
            JsonWrapper asks = json.getJsonObjectOrArray("asks");
            std::vector<PriceLevel> bidList;
            std::vector<PriceLevel> askList;
            for (int i = 0; i < bids.size(); i++) {
                JsonWrapper bidEntry = bids.getArrayAt(i);
                PriceLevel entry = PriceLevelParser::parse(bidEntry);
                bidList.push_back(entry);
            }
            for (int i = 0; i < asks.size(); i++) {
                JsonWrapper askEntry = asks.getArrayAt(i);
                PriceLevel entry = PriceLevelParser::parse(askEntry);
                askList.push_back(entry);
            }
            price.bids = bidList;
            price.asks = askList;
            return price;
        }
    };

}


#endif /* MARKETDEPTHPARSER_H */

