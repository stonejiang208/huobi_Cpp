/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CandlestickParser.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月15日, 下午8:02
 */

#ifndef CANDLESTICKPARSER_H
#define CANDLESTICKPARSER_H

namespace Huobi {

  
    class CandlestickParser {
        
    public:
        static std::vector<Candlestick>  parseArray(JsonWrapper& json) {
                std::vector<Candlestick> cans;
                std::cout<<"size: "<<std::endl;
                std::cout<<json.size()<<std::endl;
                for (int i = 0; i < json.size(); i++) {
                    JsonWrapper item = json.getJsonObjectAt(i);
                    printf("------before parse item------\n");
                    Candlestick candlestick = parse(item);
                     printf("------after parse item------\n");
                    cans.push_back(candlestick);
                }
                return cans;
           
        }

        static Candlestick parse(JsonWrapper& item) {
            Candlestick candlestick;          
             printf("------id------\n");
             try{
           candlestick.id = item.getLong("id");
             }catch(SDKException ex)
             {
                 std::cout<<ex.errorCode<<std::endl;
                  std::cout<<ex.errorMsg<<std::endl;
                 
             }
            candlestick.open = item.getDecimal("open");

            candlestick.close = item.getDecimal("close");

            candlestick.low = item.getDecimal("low");

            candlestick.high = item.getDecimal("high");

                         
            candlestick.amount = item.getDecimal("amount");

            candlestick.count = item.getLongOrDefault("count",0);
            candlestick.volume = item.getDecimal("vol");
            return candlestick;
        }
    };
}

#endif /* CANDLESTICKPARSER_H */

