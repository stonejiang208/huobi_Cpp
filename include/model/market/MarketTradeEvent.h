/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MarketTradeEvent.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月22日, 下午5:00
 */

#ifndef MARKETTRADEEVENT_H
#define MARKETTRADEEVENT_H

#include "MarketTrade.h"
namespace Huobi {

    struct MarketTradeEvent {
        std::string ch;
        long ts;
        std::vector<MarketTrade> list;
    };

}

#endif /* MARKETTRADEEVENT_H */

