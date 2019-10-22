/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MarketDetailEventParser.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月22日, 下午4:18
 */

#ifndef MARKETDETAILEVENTPARSER_H
#define MARKETDETAILEVENTPARSER_H

#include "model/market/MarketDetailEvent.h"
#include "../../../Utils/JsonWrapper.h"
#include "MarketDetailParser.h"
namespace Huobi {

    class MarketDetailEventParser {
    public:

        static MarketDetailEvent parse(JsonWrapper& json) {

            MarketDetailEvent event;
            event.ch = json.getString("ch");
            event.ts = json.getLong("ts");
            JsonWrapper tick = json.getJsonObjectOrArray("tick");
            event.detail = MarketDetailParser::parse(tick);
            return event;
        }
    };

}


#endif /* MARKETDETAILEVENTPARSER_H */

