/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MarketDetailMergedRequest.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月17日, 下午4:35
 */

#ifndef MARKETDETAILMERGEDREQUEST_H
#define MARKETDETAILMERGEDREQUEST_H

namespace Huobi {

    /**
     * The request for getting market detail merged data.
     */
    struct MarketDetailMergedRequest {

        /**
         * The request for getting market detail merged data.
         *
         * \param symbol: The symbol, like "btcusdt". To query hb10, put "hb10" at here. (mandatory)
         */

        MarketDetailMergedRequest(const std::string& symbol) : symbol(symbol) {
        }
    
        std::string symbol;
       
    };

}


#endif /* MARKETDETAILMERGEDREQUEST_H */

