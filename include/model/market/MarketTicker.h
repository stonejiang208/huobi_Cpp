/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MarketTicker.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月22日, 下午2:03
 */

#ifndef MARKETTICKER_H
#define MARKETTICKER_H

#include "constant/Decimal.h"

namespace Huobi {

    struct MarketTicker {
        
        std::string symbol;
        Decimal open;
        Decimal close;
        Decimal low;
        Decimal high;
        Decimal amount;
        long count;
        Decimal vol;

    };

}


#endif /* MARKETTICKER_H */

