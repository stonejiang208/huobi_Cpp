/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MarketClient.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月15日, 下午4:52
 */

#ifndef MARKETCLIENT_H
#define MARKETCLIENT_H


#include <vector>
#include <list>
#include <string>
#include <functional>
#include "model/market/Candlestick.h"
#include "model/market/MarketDetailMerged.h"
#include "model/market/CandlestickEvent.h"
#include"model/market/MarketDetail.h"

#include "req/market/CandlestickRequest.h"
#include "req/market/MarketDetailMergedRequest.h"
#include "req/market/SubCandlestickRequest.h"
#include "req/market/MarketDetailRequest.h"
namespace Huobi {

    /**
     * Synchronous request interface, invoking Huobi RestAPI via synchronous method.<br> All methods in
     * this interface will be blocked until the RestAPI response.
     * <p>
     * If the invoking failed or timeout, the HuobiApiException will be thrown.
     */
    struct MarketClient {
        /**
         * Get the timestamp from Huobi server. The timestamp is the Unix timestamp in millisecond.<br>
         * The count shows how many milliseconds passed from Jan 1st 1970, 00:00:00.000 at UTC.<br>
         * <br> e.g. 1546300800000 is Thu, 1st Jan 2019 00:00:00.000 UTC.
         *
         * \return The Unix timestamp at UTC in millisecond.
         */
        //  virtual long getExchangeTimestamp() = 0;

        /**
         * Get the candlestick/kline for the specified symbol. The data number is 150 as default.
         *
         * \param request The request for getting candlestick/kline data.
         * \return The list of candlestick/kline data.
         */
        virtual std::vector<Candlestick> getCandlestick(const CandlestickRequest& request) = 0;

        virtual void subCandlestick(const SubCandlestickRequest& req, const std::function<void( const CandlestickEvent&) > callback) = 0;
        //      
        //         /**
        //         * Get the last trade with their price, volume and direction.
        //         *
        //         * \param symbol The symbol, like "btcusdt". (mandatory)
        //         * \return The last trade with price and amount.
        //         */
        //        virtual Trade getLastTrade(const char* symbol) = 0;
        //        /**
        //         * Get the most recent trades with their price, volume and direction.
        //         *
        //         * \param symbol The symbol, like "btcusdt". (mandatory)
        //         * \param size   The  number of historical trade requested, range [1 - 2000] (mandatory)
        //         * \return The list of trade.
        //         */
        //        virtual std::vector<Trade> getHistoricalTrade(const char* symbol, int size) = 0;
        //        /**
        //         * Get the Market Depth of a symbol.
        //         *
        //         * \param symbol The symbol, like "btcusdt". (mandatory)
        //         * \param size   The maximum number of Market Depth requested. range [1 - 150] (mandatory)
        //         * \return Market Depth data.
        //         */
        //        virtual PriceDepth getPriceDepth(const char* symbol, int size) = 0;
        //       

        virtual MarketDetailMerged getMarketDetailMerged(const MarketDetailMergedRequest& request) = 0;

        virtual MarketDetail getMarketDetail(const MarketDetailRequest& request) = 0;

        //        /**
        //         * Get all the trading assets and currencies supported in huobi.pro. The information of trading
        //         * instrument, including base currency, quote precision, etc.
        //         *
        //         * \return The information of trading instrument and currencies.
        //         */
        //        virtual ExchangeInfo getExchangeInfo() = 0;
        //        /**
        //         * Get the best bid and ask.
        //         *
        //         * \param symbol The symbol, like "btcusdt". (mandatory)
        //         * \return The best quote.
        //         */
        //        virtual BestQuote getBestQuote(const char* symbol) = 0;
        //        
        //
        //       
        //        virtual LastTradeAndBestQuote getLastTradeAndBestQuote(const char* symbol) = 0;
        //             
        //       
        //        /**
        //         * Get the basic information of ETF creation and redemption, as well as ETF constituents,
        //         * including max amount of creation, min amount of creation, max amount of redemption, min amount
        //         * of redemption, creation fee rate, redemption fee rate, eft create/redeem status.
        //         *
        //         * \param etfSymbol The symbol, currently only support hb10. (mandatory)
        //         * \return The etf configuration information.
        //         */
        //        virtual EtfSwapConfig getEtfSwapConfig(const char* etfSymbol) = 0;
        //      
        //        /**
        //         * Get the latest candlestick/kline for the etf.
        //         *
        //         * \param etfSymbol The symbol, currently only support hb10. (mandatory)
        //         * \param interval  The candlestick/kline interval, MIN1, MIN5, DAY1 etc. (mandatory)
        //         * \param limit     The maximum number of candlestick/kline requested. Range [1 - 2000]
        //         *                  (optional)
        //         * \return The list of candlestick/kline data.
        //         */
        //        virtual std::vector<Candlestick> getEtfCandlestick(const char* etfSymbol, CandlestickInterval interval,
        //                int limit = 150) = 0;
        //        
        //        
        //        /**
        //         * Get all Huobi support symbols
        //         * \return The information of symbols.
        //         */
        //        virtual std::vector<Symbols> getSymbols() = 0;
        //        /**
        //         * Get all Huobi support currencies.
        //         * \return The list of currencies.
        //         */
        //        virtual std::vector<std::string> getCurrencies() = 0;
        //
        //        /**
        //         * Get the lastest trade with their price, volume and direction.
        //         *
        //         * \param symbol The symbol, like "btcusdt". (mandatory)
        //         * \return The last trade with price and amount.
        //         */
        //        virtual Trade getMarketTrade(const char* symbol) = 0;
    };

}

#endif /* MARKETCLIENT_H */

