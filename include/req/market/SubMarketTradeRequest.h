/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SubMarketTradeRequest.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月22日, 下午4:58
 */

#ifndef SUBMARKETTRADEREQUEST_H
#define SUBMARKETTRADEREQUEST_H

namespace Huobi {

    struct SubMarketTradeRequest {

        SubMarketTradeRequest(const std::string& symbol) : symbol(symbol) {
        }

        std::string symbol;

    };

}

#endif /* SUBMARKETTRADEREQUEST_H */

