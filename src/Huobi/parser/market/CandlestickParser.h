/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CandlestickParser.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月15日, 下午8:02
 */

#ifndef CANDLESTICKPARSER_H
#define CANDLESTICKPARSER_H
#include "../../../Utils/JsonDocument.h"
#include "../../../Utils/JsonWrapper.h"
namespace Huobi {

    class CandlestickParser {
    public:

        static std::vector<Candlestick> parseArray(JsonWrapper& json) {
            std::vector<Candlestick> cans;
            for (int i = 0; i < json.size(); i++) {
                JsonWrapper item = json.getJsonObjectAt(i);
                Candlestick candlestick = parse(item);
                cans.push_back(candlestick);
            }
            return cans;

        }

        static Candlestick parse(JsonWrapper& item) {
            Candlestick candlestick;
            candlestick.id = item.getLong("id");
            candlestick.open = item.getDecimal("open");
            candlestick.close = item.getDecimal("close");
            candlestick.low = item.getDecimal("low");
            candlestick.high = item.getDecimal("high");
            candlestick.amount = item.getDecimal("amount");
            candlestick.count = item.getLongOrDefault("count", 0);
            candlestick.volume = item.getDecimal("vol");
            return candlestick;
        }
    };
}

#endif /* CANDLESTICKPARSER_H */

