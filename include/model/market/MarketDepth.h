/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MarketDepth.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月22日, 下午2:29
 */

#ifndef MARKETDEPTH_H
#define MARKETDEPTH_H
#include "PriceLevel.h"
namespace Huobi {

    struct MarketDepth {
        long version;
        long ts;
        std::vector<PriceLevel> bids;
        std::vector<PriceLevel> asks;
    };

}

#endif /* MARKETDEPTH_H */

