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
        std::cout << "获取响应数据" << std::endl;
        JsonWrapper json = restConnection->executeGet(REST_CANDLESTICK_URL, builder);
        JsonWrapper data = json.getJsonObjectOrArray("data");
        //解析数据
        std::vector<Candlestick> cans = CandlestickParser::parseArray(data);
        return cans;
    }

    void HuobiMarketService::subCandlestick(const SubCandlestickRequest& req, const std::function<void( const CandlestickEvent&) > callback) {
        InputChecker::checker()
                ->shouldNotNull(req.interval.getValue(), "interval")
                ->checkCallback(callback);
        std::list<std::string> symbols = SymbolUtils::parseSymbols(req.symbol.c_str());
        std::list<std::string> commandList;
        for (std::string symbol : symbols) {
            std::string topic = WEBSOCKET_CANDLESTICK_TOPIC;
            topic.replace(topic.find("$symbol"), 7, symbol);
            topic.replace(topic.find("$period"), 7, req.interval.getValue());
            std::cout << topic << std::endl;

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


}