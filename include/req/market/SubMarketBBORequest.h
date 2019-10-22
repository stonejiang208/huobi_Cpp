/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SubMarketBBORequest.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月22日, 下午5:22
 */

#ifndef SUBMARKETBBOREQUEST_H
#define SUBMARKETBBOREQUEST_H

namespace Huobi {

    struct SubMarketBBORequest {

        SubMarketBBORequest(const std::string& symbol) : symbol(symbol) {
        }

        std::string symbol;

    };

}

#endif /* SUBMARKETBBOREQUEST_H */

