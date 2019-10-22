/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MarketTradeRequest.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月22日, 下午3:21
 */

#ifndef MARKETTRADEREQUEST_H
#define MARKETTRADEREQUEST_H

namespace Huobi {

    struct MarketTradeRequest {

        MarketTradeRequest(const std::string& symbol) : symbol(symbol) {
        }

        std::string symbol;
    };
}

#endif /* MARKETTRADEREQUEST_H */

