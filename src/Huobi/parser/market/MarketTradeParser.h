/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MarketTradeParser.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月22日, 下午3:34
 */

#ifndef MARKETTRADEPARSER_H
#define MARKETTRADEPARSER_H

namespace Huobi{
    class MarketTradeParser{
    
    public:
        static std::vector<MarketTrade> parseArray(JsonWrapper json) {
            std::vector<MarketTrade> marketTradeVec;
            JsonWrapper data = json.getJsonObjectOrArray("data");
            for (int i = 0; i < data.size(); i++) {
                JsonWrapper item = data.getJsonObjectAt(i);
                marketTradeVec.push_back(parse(item));
            }
            return marketTradeVec;
        }
        
        static MarketTrade parse(JsonWrapper item) {
            MarketTrade trade;
            trade.price = item.getDecimal("price");
            trade.amount = item.getDecimal("amount");
            trade.tradeId = item.getLong("trade-id");
            trade.ts = item.getLong("ts");
            trade.id = item.getLong("id");
            trade.direction = TradeDirection::lookup(item.getString("direction"));
            return trade;
        }
    };

}

#endif /* MARKETTRADEPARSER_H */

