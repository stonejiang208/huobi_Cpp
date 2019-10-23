/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include"./HuobiMarketService.h"
#include "../Utils/InputChecker.h"
#include "../Utils/SymbolUtils.h"
#include "../Utils/JsonWriter.h"
#include "../Utils/TimeService.h"
#include "parser/market/CandlestickEventParser.h"
#include "parser/market/MarketTickerParser.h"
#include "parser/market/MarketDepthParser.h"
#include "parser/market/MarketTradeParser.h"
#include "parser/market/MarketTradeEventParser.h"
#include "parser/market/MarketDetailEventParser.h"
#include "parser/market/MarketDepthEventParser.h"
#include "parser/market/MarketBBOEventParser.h"
namespace Huobi {

    std::vector<Candlestick> HuobiMarketService::getCandlestick(
            const CandlestickRequest& request) {
        //参数检查
        InputChecker::checker()
                ->checkSymbol(request.symbol)
                ->checkRange(request.size, 0, 2000, "size");
        //参数构建
        UrlParamsBuilder builder;
        builder.putUrl("symbol", request.symbol)
                .putUrl("period", request.interval.getValue())
                .putUrl("size", request.size);
        //获取响应数据
       
        JsonWrapper json = restConnection->executeGet(REST_CANDLESTICK_URL, builder);
        JsonWrapper data = json.getJsonObjectOrArray("data");
        //解析数据
        std::vector<Candlestick> cans = CandlestickParser::parseArray(data);
        return cans;
    }

    void HuobiMarketService::subCandlestick(const SubCandlestickRequest& req, const std::function<void( const CandlestickEvent&) > callback) {
        InputChecker::checker()
                ->shouldNotNull(req.symbol, "symbol")
                ->shouldNotNull(req.interval.getValue(), "interval")
                ->checkCallback(callback);
        std::list<std::string> symbols = SymbolUtils::parseSymbols(req.symbol.c_str());
        std::list<std::string> commandList;
        for (std::string symbol : symbols) {
            std::string topic = WEBSOCKET_CANDLESTICK_TOPIC;
            topic.replace(topic.find("$symbol"), 7, symbol);
            topic.replace(topic.find("$period"), 7, req.interval.getValue());
            JsonWriter writer;
            writer.put("sub", topic);
            writer.put("id", std::to_string(TimeService::getCurrentTimeStamp()));
            commandList.push_back(writer.toJsonString());

        }
        HuobiWebSocketConnection<CandlestickEvent>::createMarketConnection(commandList, callback, options, CandlestickEventParser::parse);
    }

    MarketDetailMerged HuobiMarketService::getMarketDetailMerged(const MarketDetailMergedRequest& request) {

        InputChecker::checker()->checkSymbol(request.symbol);
        UrlParamsBuilder builder;
        builder.putUrl("symbol", request.symbol);
        JsonWrapper json = restConnection->executeGet(REST_MARKET_DETAIL_MERGED_PATH, builder);

        JsonWrapper tick = json.getJsonObjectOrArray("tick");
        MarketDetailMerged marketDetailMerged = MarketDetailMergedParser::parse(tick);
        return marketDetailMerged;
    }

    MarketDetail HuobiMarketService::getMarketDetail(const MarketDetailRequest& request) {

        InputChecker::checker()->checkSymbol(request.symbol);
        UrlParamsBuilder builder;
        builder.putUrl("symbol", request.symbol);
        JsonWrapper json = restConnection->executeGet(REST_MARKET_DETAIL_PATH, builder);

        JsonWrapper tick = json.getJsonObjectOrArray("tick");
        MarketDetail marketDetail = MarketDetailParser::parse(tick);
        return marketDetail;
    }

    void HuobiMarketService::subMarketDetail(const SubMarketDetailRequest& request, const std::function<void( const MarketDetailEvent&) > callback) {

        InputChecker::checker()
                ->shouldNotNull(request.symbol, "symbol")
                ->checkCallback(callback);

        std::list<std::string> symbols = SymbolUtils::parseSymbols(request.symbol.c_str());
        std::list<std::string> commandList;
        for (std::string symbol : symbols) {
            std::string topic = WEBSOCKET_MARKET_DETAIL_TOPIC;
            topic.replace(topic.find("$symbol"), 7, symbol);


            JsonWriter writer;
            writer.put("sub", topic);
            writer.put("id", std::to_string(TimeService::getCurrentTimeStamp()));
            commandList.push_back(writer.toJsonString());

        }
        HuobiWebSocketConnection<MarketDetailEvent>::createMarketConnection(commandList, callback, options, MarketDetailEventParser::parse);

    }

    std::vector<MarketTicker> HuobiMarketService::getTickers() {

        UrlParamsBuilder builder;
        JsonWrapper json = restConnection->executeGet(REST_MARKET_TICKERS_PATH, builder);
        JsonWrapper data = json.getJsonObjectOrArray("data");
        std::vector<MarketTicker> marketTickerVec = MarketTickerParser::parseArray(data);
        return marketTickerVec;

    }

    MarketDepth HuobiMarketService::getMarketDepth(const MarketDepthRequest& request) {

        InputChecker::checker()
                ->checkSymbol(request.symbol)
                ->shouldNotNull(request.type.getValue(), "type");

        int size = request.depth.getValue().compare("") ? std::atoi(request.depth.getValue().c_str()) : 0;

        // 参数构建
        UrlParamsBuilder builder;
        builder.putUrl("symbol", request.symbol)
                .putUrl("depth", size)
                .putUrl("type", request.type.getValue());

        JsonWrapper json = restConnection->executeGet(REST_MARKET_DEPTH_PATH, builder);
        JsonWrapper tick = json.getJsonObjectOrArray("tick");
        MarketDepth marketDepth = MarketDepthParser::parse(tick);
        return marketDepth;
    }

    void HuobiMarketService::subMarketDepth(const SubMarketDepthRequest& request, const std::function<void( const MarketDepthEvent&) > callback) {

        InputChecker::checker()
                ->shouldNotNull(request.symbol, "symbol")
                ->shouldNotNull(request.type.getValue(), "type")
                ->checkCallback(callback);
        std::list<std::string> symbols = SymbolUtils::parseSymbols(request.symbol.c_str());
        std::list<std::string> commandList;
        for (std::string symbol : symbols) {
            std::string topic = WEBSOCKET_MARKET_DEPTH_TOPIC;
            topic.replace(topic.find("$symbol"), 7, symbol);
            topic.replace(topic.find("$type"), 5, request.type.getValue());
            JsonWriter writer;
            writer.put("sub", topic);
            writer.put("id", std::to_string(TimeService::getCurrentTimeStamp()));
            commandList.push_back(writer.toJsonString());

        }
        HuobiWebSocketConnection<MarketDepthEvent>::createMarketConnection(commandList, callback, options, MarketDepthEventParser::parse);

    }

    MarketTrade HuobiMarketService::getMarketTrade(const MarketTradeRequest& request) {

        InputChecker::checker()
                ->checkSymbol(request.symbol);
        UrlParamsBuilder builder;
        builder.putUrl("symbol", request.symbol);
        JsonWrapper json = restConnection->executeGet(REST_MARKET_TRADE_PATH, builder);
        JsonWrapper tick = json.getJsonObjectOrArray("tick");
        JsonWrapper data = tick.getJsonObjectOrArray("data");
        JsonWrapper item =data.getJsonObjectAt(0);
        MarketTrade marketTrade = MarketTradeParser::parse(item);
        return marketTrade;
    }

    void HuobiMarketService::subMarketTrade(const SubMarketTradeRequest& request, const std::function<void( const MarketTradeEvent&) > callback) {

        InputChecker::checker()
                ->shouldNotNull(request.symbol, "symbol")
                ->checkCallback(callback);
        std::list<std::string> symbols = SymbolUtils::parseSymbols(request.symbol.c_str());
        std::list<std::string> commandList;
        for (std::string symbol : symbols) {
            std::string topic = WEBSOCKET_MARKET_TRADE_TOPIC;
            topic.replace(topic.find("$symbol"), 7, symbol);
            JsonWriter writer;
            writer.put("sub", topic);
            writer.put("id", std::to_string(TimeService::getCurrentTimeStamp()));
            commandList.push_back(writer.toJsonString());

        }
        HuobiWebSocketConnection<MarketTradeEvent>::createMarketConnection(commandList, callback, options, MarketTradeEventParser::parse);

    }

    std::vector<MarketTrade> HuobiMarketService::getMarketHistoryTrade(const MarketHistoryTradeRequest& request) {

        InputChecker::checker()
                ->checkSymbol(request.symbol)
                ->checkRange(request.size, 0, 2000, "size");

        UrlParamsBuilder builder;
        builder.putUrl("symbol", request.symbol)
                .putUrl("size", request.size);
        JsonWrapper json = restConnection->executeGet(REST_MARKET_HISTORY_TRADE_PATH, builder);

        std::vector<MarketTrade> trades;
        JsonWrapper dataArray = json.getJsonObjectOrArray("data");
        for (int i = 0; i < dataArray.size(); i++) {
            JsonWrapper item = dataArray.getJsonObjectAt(i);
            JsonWrapper dataArrayIn = item.getJsonObjectOrArray("data");
            for (int j = 0; j < dataArrayIn.size(); j++) {
                JsonWrapper itemIn = dataArrayIn.getJsonObjectAt(j);
                MarketTrade trade = MarketTradeParser::parse(itemIn);
                trades.push_back(trade);
            }
        }
        return trades;

    }

    void HuobiMarketService::subMarketBBO(const SubMarketBBORequest& request, const std::function<void( const MarketBBOEvent&) > callback) {

        InputChecker::checker()
                ->shouldNotNull(request.symbol, "symbol")
                ->checkCallback(callback);
        std::list<std::string> symbols = SymbolUtils::parseSymbols(request.symbol.c_str());
        std::list<std::string> commandList;
        for (std::string symbol : symbols) {
            std::string topic = WEBSOCKET_MARKET_BBO_TOPIC;
            topic.replace(topic.find("$symbol"), 7, symbol);
            JsonWriter writer;
            writer.put("sub", topic);
            writer.put("id", std::to_string(TimeService::getCurrentTimeStamp()));
            commandList.push_back(writer.toJsonString());

        }
        HuobiWebSocketConnection<MarketBBOEvent>::createMarketConnection(commandList, callback, options, MarketBBOEventParser::parse);


    }


}