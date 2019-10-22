/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MarketBBOEventParser.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月22日, 下午5:29
 */

#ifndef MARKETBBOEVENTPARSER_H
#define MARKETBBOEVENTPARSER_H

#include "model/market/MarketBBOEvent.h"
#include "../../../Utils/JsonWrapper.h"
#include "MarketBBOParser.h"
namespace Huobi {

    class MarketBBOEventParser {
    public:

        static MarketBBOEvent parse(JsonWrapper& json) {

            MarketBBOEvent event;
            event.ch=json.getString("ch");
            event.ts = json.getLong("ts");
            JsonWrapper tick=json.getJsonObjectOrArray("tick");
            event.bbo = MarketBBOParser::parse(tick);
            return event;
        }
    };

}

#endif /* MARKETBBOEVENTPARSER_H */

