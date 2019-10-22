/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HuobiMarketService.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月16日, 下午7:36
 */

#ifndef HUOBIMARKETSERVICE_H
#define HUOBIMARKETSERVICE_H

#include <string>
#include "client/MarketClient.h"
#include "connection/HuobiRestConnection.h"
#include "connection/HuobiWebSocketConnection.h"

#include "../Utils/InputChecker.h"

#include "parser/market/CandlestickParser.h"
#include "parser/market/MarketDetailMergedParser.h"
#include "parser/market/MarketDetailParser.h"
#include "../options/HuobiOptions.h"

namespace Huobi {

    class HuobiMarketService : public MarketClient {
    private:
        HuobiRestConnection* restConnection;
        HuobiOptions options;
    public:
        const char* REST_CANDLESTICK_URL = "/market/history/kline";
        const char* REST_MARKET_DETAIL_MERGED_PATH = "/market/detail/merged";
        const char* REST_MARKET_DETAIL_PATH = "/market/detail";
        const char* REST_MARKET_TICKERS_PATH = "/market/tickers";
        const char* REST_MARKET_DEPTH_PATH = "/market/depth";
        const char* REST_MARKET_TRADE_PATH = "/market/trade";
        const char* REST_MARKET_HISTORY_TRADE_PATH = "/market/history/trade";

    public:
        const std::string WEBSOCKET_CANDLESTICK_TOPIC = "market.$symbol.kline.$period";
        const std::string WEBSOCKET_MARKET_DETAIL_TOPIC = "market.$symbol.detail";
        const std::string WEBSOCKET_MARKET_DEPTH_TOPIC = "market.$symbol.depth.$type";
        const std::string WEBSOCKET_MARKET_TRADE_TOPIC = "market.$symbol.trade.detail";
        const std::string WEBSOCKET_MARKET_BBO_TOPIC = "market.$symbol.bbo";


    public:

        HuobiMarketService(HuobiOptions& op) {
            options = op;
            restConnection = new HuobiRestConnection(op);
        }

        std::vector<Candlestick> getCandlestick(const CandlestickRequest& request) override;

        void subCandlestick(const SubCandlestickRequest& req, const std::function<void( const CandlestickEvent&) > callback) override;

        MarketDetailMerged getMarketDetailMerged(const MarketDetailMergedRequest& request) override;

        MarketDetail getMarketDetail(const MarketDetailRequest& request) override;

        void subMarketDetail(const SubMarketDetailRequest& request, const std::function<void( const MarketDetailEvent&) > callback) override;


        std::vector<MarketTicker> getTickers() override;

        MarketDepth getMarketDepth(const MarketDepthRequest& request) override;

        void subMarketDepth(const SubMarketDepthRequest& request, const std::function<void( const MarketDepthEvent&) > callback) override;

        MarketTrade getMarketTrade(const MarketTradeRequest& request) override;

        void subMarketTrade(const SubMarketTradeRequest& request, const std::function<void( const MarketTradeEvent&) > callback) override;

        std::vector<MarketTrade> getMarketHistoryTrade(const MarketHistoryTradeRequest& request) override;

        void subMarketBBO(const SubMarketBBORequest& request, const std::function<void( const MarketBBOEvent&) > callback) override;


    };
}
#endif /* HUOBIMARKETSERVICE_H */

