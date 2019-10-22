/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MarketDepthEventParser.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月22日, 下午4:49
 */

#ifndef MARKETDEPTHEVENTPARSER_H
#define MARKETDEPTHEVENTPARSER_H

#include "model/market/MarketDepthEvent.h"
#include "../../../Utils/JsonWrapper.h"
#include "MarketDepthParser.h"
namespace Huobi {

    class MarketDepthEventParser {
    public:

        static MarketDepthEvent parse(JsonWrapper& json) {

            MarketDepthEvent event;
            event.ch=json.getString("ch");
            event.ts = json.getLong("ts");
            JsonWrapper tick=json.getJsonObjectOrArray("tick");
            event.depth = MarketDepthParser::parse(tick);
            return event;
        }
    };

}

#endif /* MARKETDEPTHEVENTPARSER_H */

