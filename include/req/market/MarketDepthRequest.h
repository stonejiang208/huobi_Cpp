/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MarketDepthRequest.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月22日, 下午2:31
 */

#ifndef MARKETDEPTHREQUEST_H
#define MARKETDEPTHREQUEST_H
#include "constant/enums.h"
namespace Huobi {

    struct MarketDepthRequest {

        MarketDepthRequest(const std::string& symbol, const DepthStep& type) : symbol(symbol), type(type) {
        }

        MarketDepthRequest(const std::string& symbol, const DepthStep& type, const DepthSize& depth) : symbol(symbol), type(type), depth(depth) {
        }

        std::string symbol;
        DepthSize depth;
        DepthStep type;

    };

}

#endif /* MARKETDEPTHREQUEST_H */

