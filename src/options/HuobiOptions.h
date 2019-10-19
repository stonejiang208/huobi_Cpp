/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HuobiOptions.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月16日, 上午11:43
 */

#ifndef HUOBIOPTIONS_H
#define HUOBIOPTIONS_H
#include "constant/Options.h"
namespace Huobi {

    struct HuobiOptions/* : public Options */ {
        const char* restHost = "https://api.huobi.so";
        const char* websocketHost = "wss://api.huobi.so";
        const char* apiKey="";
        const char* secretKey="";

        //        exchange=ExchangeEnum::huobi;

        //        void setOptionsApiKey(const char* apiKey);
        //        void setOptionsSecretKey(const char* secretKey) ;
        //        void setExchange(ExchangeEnum exchange) ;

    };

}


#endif /* HUOBIOPTIONS_H */

