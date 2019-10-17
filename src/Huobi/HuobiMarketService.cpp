/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include"Huobi/HuobiMarketService.h"
#include "parser/CandlestickParser.h"

namespace Huobi {
       

    std::vector<Candlestick> HuobiMarketService::getCandlestick(
            const CandlestickRequest& request) {
        UrlParamsBuilder builder;
        builder.putUrl("symbol", request.symbol)
                .putUrl("period", request.interval.getValue())
                .putUrl("size", request.size);             

       JsonWrapper json= restConnection->executeGet(REST_CANDLESTICK_URL,builder);
       JsonWrapper data = json.getJsonObjectOrArray("data");
       std::vector<Candlestick> cans= CandlestickParser::parseArray(data);
       return cans;
    }
         

}