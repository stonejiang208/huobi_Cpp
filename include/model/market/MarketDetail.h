/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MarketDetail.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月22日, 上午11:54
 */

#ifndef MARKETDETAIL_H
#define MARKETDETAIL_H

#include "constant/Decimal.h"

namespace Huobi {

    struct MarketDetail {
        long id;
        Decimal open;
        Decimal close;
        Decimal low;
        Decimal high;
        long count;
        Decimal vol;
        Decimal amount;
        long version;
    };

}

#endif /* MARKETDETAIL_H */

