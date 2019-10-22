/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SubMarketDepthRequest.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月22日, 下午4:28
 */

#ifndef SUBMARKETDEPTHREQUEST_H
#define SUBMARKETDEPTHREQUEST_H

#include "constant/enums.h"


namespace Huobi {

    struct SubMarketDepthRequest {

        SubMarketDepthRequest(const std::string& symbol, const DepthStep& type) : symbol(symbol), type(type) {
        }

        std::string symbol;
        DepthStep type;

    };

}




#endif /* SUBMARKETDEPTHREQUEST_H */

