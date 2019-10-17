/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HuobiMarketService.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月16日, 下午7:36
 */

#ifndef HUOBIMARKETSERVICE_H
#define HUOBIMARKETSERVICE_H

#include "MarketClient.h"
#include "/root/huobi_Cpp/src/Huobi/connection/HuobiRestConnection.h"
#include "/root/huobi_Cpp/src/Huobi/parser/CandlestickParser.h"
namespace Huobi {

    class HuobiMarketService : public MarketClient {
    private:
        HuobiRestConnection* restConnection;
    public:
        const char* REST_CANDLESTICK_URL = "/market/history/kline";
    public:

        HuobiMarketService(HuobiOptions& op) {

            restConnection = new HuobiRestConnection(op);
        }
     
        std::vector<Candlestick> getCandlestick(const CandlestickRequest& request);
       
    };
}
#endif /* HUOBIMARKETSERVICE_H */

