/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MarketDetailEvent.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月22日, 下午4:06
 */

#ifndef MARKETDETAILEVENT_H
#define MARKETDETAILEVENT_H
#include "MarketDetail.h"
namespace Huobi {

    struct MarketDetailEvent {
        std::string ch;
        long ts;
        MarketDetail detail;
    };

}

#endif /* MARKETDETAILEVENT_H */

