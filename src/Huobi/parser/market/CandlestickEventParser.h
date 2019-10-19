/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CandlestickEventParser.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月18日, 上午10:19
 */

#ifndef CANDLESTICKEVENTPARSER_H
#define CANDLESTICKEVENTPARSER_H
#include "model/market/CandlestickEvent.h"
#include "../../../Utils/JsonWrapper.h"
#include "CandlestickParser.h"
namespace Huobi {

    class CandlestickEventParser {
    public:

        static CandlestickEvent parse(JsonWrapper& json) {

            CandlestickEvent event;
            event.ch=json.getString("ch");
            event.ts = json.getLong("ts");
            JsonWrapper tick=json.getJsonObjectOrArray("tick");
            event.candlestick = CandlestickParser::parse(tick);
            return event;
        }
    };

}

#endif /* CANDLESTICKEVENTPARSER_H */

