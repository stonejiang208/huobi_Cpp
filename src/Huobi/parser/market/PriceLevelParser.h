/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PriceLevelParser.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月17日, 下午5:25
 */

#ifndef PRICELEVELPARSER_H
#define PRICELEVELPARSER_H
namespace Huobi
{

    class PriceLevelParser {
    public:

        static PriceLevel parse(JsonWrapper& json) {
            PriceLevel priceLevel;
            priceLevel.price = json.getDecimalAt(0);
            priceLevel.amount = json.getDecimalAt(1);
            return priceLevel;

        }

    };
}

#endif /* PRICELEVELPARSER_H */

