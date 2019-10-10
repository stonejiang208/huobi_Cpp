/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BestQuote.h
 * Author: yuanxueqi
 *
 * Created on 2019年3月18日, 下午11:57
 */
#ifndef BESTQUOTE_H
#define BESTQUOTE_H

#include "Huobi/Decimal.h"
#include "/root/huobi_Cpp/src/TimeService.h"
#include "/root/huobi_Cpp/src/RestApiJsonParser.h"
#include "/root/huobi_Cpp/src/Utils/JsonWrapper.h"
namespace Huobi {

    /**
     * The best bid/ask consisting of price and amount.
     */
    struct BestQuote {
        /**
         * The Unix formatted timestamp in UTC.
         */
        long timestamp = 0;

        /**
         * The best bid price.
         */
        Decimal askPrice;

        /**
         * The best bid amount.
         */
        Decimal askAmount;

        /**
         * The best ask price.
         */
        Decimal bidPrice;

        /**
         * The best ask amount.
         */
        Decimal bidAmount;


        static RestApiJsonParser<BestQuote > getParser() {

            RestApiJsonParser<BestQuote> res;
            res.parseJson = [](JsonWrapper json) {            
                BestQuote bestQuote = parse(json);
                return bestQuote;
            };
            return res;
        }

        static BestQuote parse(JsonWrapper json) {
            BestQuote bestQuote;
            bestQuote.timestamp = TimeService::convertCSTInMillisecondToUTC(json.getLong("ts"));
            JsonWrapper tick = json.getJsonObjectOrArray("tick");
            JsonWrapper askArray = tick.getJsonObjectOrArray("ask");
            bestQuote.askPrice = askArray.getDecimalAt(0);
            bestQuote.askAmount = askArray.getDecimalAt(1);
            JsonWrapper bidArray = tick.getJsonObjectOrArray("bid");
            bestQuote.bidPrice = bidArray.getDecimalAt(0);
            bestQuote.bidAmount = bidArray.getDecimalAt(1);
            return bestQuote;
        }
    };

}




#endif /* BESTQUOTE_H */

