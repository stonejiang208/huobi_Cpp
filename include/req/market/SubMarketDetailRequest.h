/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SubMarketDetailRequest.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月22日, 下午4:07
 */

#ifndef SUBMARKETDETAILREQUEST_H
#define SUBMARKETDETAILREQUEST_H

namespace Huobi {

    struct SubMarketDetailRequest {

        SubMarketDetailRequest(const std::string& symbol) : symbol(symbol) {
        }

        std::string symbol;

    };

}


#endif /* SUBMARKETDETAILREQUEST_H */

