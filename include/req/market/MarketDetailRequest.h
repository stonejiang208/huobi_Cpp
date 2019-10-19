/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MarketDetailRequest.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月22日, 上午11:47
 */

#ifndef MARKETDETAILREQUEST_H
#define MARKETDETAILREQUEST_H
#include <string>

namespace Huobi {

    struct MarketDetailRequest {

        MarketDetailRequest(const std::string& symbol) : symbol(symbol) {
        }

        std::string symbol;
    };
}

#endif /* MARKETDETAILREQUEST_H */

