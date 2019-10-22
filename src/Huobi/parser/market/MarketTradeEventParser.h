/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MarketTradeEventParser.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月22日, 下午5:05
 */

#ifndef MARKETTRADEEVENTPARSER_H
#define MARKETTRADEEVENTPARSER_H


#include "model/market/MarketTradeEvent.h"
#include "../../../Utils/JsonWrapper.h"
#include "MarketTradeParser.h"
namespace Huobi {

    class MarketTradeEventParser {
    public:

        static MarketTradeEvent parse(JsonWrapper& json) {

            MarketTradeEvent event;
            event.ch = json.getString("ch");
            event.ts = json.getLong("ts");
            JsonWrapper tick = json.getJsonObjectOrArray("tick");
            event.list = MarketTradeParser::parseArray(tick);
            return event;
        }
    };

}


#endif /* MARKETTRADEEVENTPARSER_H */

