/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MarketHistoryTradeRequest.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月22日, 下午3:43
 */

#ifndef MARKETHISTORYTRADEREQUEST_H
#define MARKETHISTORYTRADEREQUEST_H

namespace Huobi {

    struct MarketHistoryTradeRequest {

        MarketHistoryTradeRequest(const std::string& symbol, int size) : symbol(symbol), size(size) {
        }

        MarketHistoryTradeRequest(const std::string& symbol) : symbol(symbol) {
        }
        std::string symbol;
        int size = 0;
    };
}


#endif /* MARKETHISTORYTRADEREQUEST_H */

