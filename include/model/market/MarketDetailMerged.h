/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MarketDetailMerged.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月17日, 下午4:17
 */

#ifndef MARKETDETAILMERGED_H
#define MARKETDETAILMERGED_H
#include "constant/Decimal.h"
#include "PriceLevel.h"
namespace Huobi {

    struct MarketDetailMerged {
        long id;
        Decimal amount;
        long count;
        Decimal open;
        Decimal close;
        Decimal low;
        Decimal high;
        Decimal vol;
        PriceLevel bid;
        PriceLevel ask;
    };

}

#endif /* MARKETDETAILMERGED_H */

