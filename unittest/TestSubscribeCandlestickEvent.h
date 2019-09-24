/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestSubscribeCandlestickEvent.h
 * Author: yuanxueqi
 *
 * Created on 2019年3月26日, 下午5:09
 */

#ifndef TESTSUBSCRIBECANDLESTICKEVENT_H
#define TESTSUBSCRIBECANDLESTICKEVENT_H

#include <gtest/gtest.h>
#include <../src/WebSocketApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"
#include <list>
using namespace Huobi;

TEST(TestSubscribeCandlestickEvent, request) {

    SubscriptionOptions op;
    WebSocketApiImpl* impl = new WebSocketApiImpl();
    std::list<std::string> symbols;
    symbols.push_back("btcusdt");
    auto request = impl->subscribeCandlestickEvent(symbols,CandlestickInterval::min1,[](const CandlestickEvent&){}, nullptr);
    std::list<std::string> dataToBeSend;
    request->connectionHandler(dataToBeSend);
    std::string subscription = dataToBeSend.back();
    ASSERT_TRUE(subscription.find("btcusdt.kline") != std::string::npos);
}

TEST(TestSubscribeCandlestickEvent, multiSymbols) {
    
SubscriptionOptions op;
    WebSocketApiImpl* impl = new WebSocketApiImpl();
    std::list<std::string> symbols;
    symbols.push_back("btcusdt");
    symbols.push_back("btcht");

    auto request = impl->subscribeCandlestickEvent(symbols,CandlestickInterval::min1,[](const CandlestickEvent&){}, nullptr);
    std::list<std::string> dataToBeSend;
    request->connectionHandler(dataToBeSend);
    std::string subscriptionf = dataToBeSend.back();
    dataToBeSend.pop_back();
    ASSERT_TRUE(subscriptionf.find("btcht.kline") != std::string::npos);
    std::string subscriptions = dataToBeSend.back();
    ASSERT_TRUE(subscriptions.find("btcusdt.kline") != std::string::npos);
    
}

#endif /* TESTSUBSCRIBECANDLESTICKEVENT_H */

