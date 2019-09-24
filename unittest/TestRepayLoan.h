/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestRepayLoan.h
 * Author: yuanxueqi
 *
 * Created on 2019年3月26日, 下午5:27
 */

#ifndef TESTREPAYLOAN_H
#define TESTREPAYLOAN_H
#include <gtest/gtest.h>
#include <../src/RestApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"

using namespace Huobi;

TEST(TestRepayLoan, request) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    auto request = impl->repayLoan(12345l, Decimal("1.1"));
    ASSERT_EQ("POST", request->method);
    ASSERT_TRUE(request->path.find("/v1/margin/orders/12345/repay") != std::string::npos);
    ASSERT_TRUE(request->path.find("Signature") != std::string::npos);
    JsonDocument doc;
    JsonWrapper querier = doc.parseFromString(request->postbody);
    ASSERT_STREQ("1.1", querier.getString("amount"));
}

TEST(TestRepayLoan, NullId) {

    RestApiImpl* impl = new RestApiImpl("12345", "67890");

    EXPECT_THROW(impl->repayLoan(0, Decimal("1.1")), HuobiApiException);
}
TEST(TestRepayLoan, NullAmount) {

    RestApiImpl* impl = new RestApiImpl();
    EXPECT_THROW(impl->repayLoan(1234, Decimal("0")), HuobiApiException);
}

TEST(TestRepayLoan, Result_Normal) {
    std::string data = "{\n"
            "  \"status\": \"ok\",\n"
            "  \"data\": 700\n"
            "}";
            RestApiImpl* impl = new RestApiImpl("12345", "67890");

            auto request = impl->repayLoan(12345l, Decimal("1.1"));
            JsonWrapper json = JsonDocument().parseFromString(data.c_str());
            auto result = request->jsonParser(json);
            ASSERT_EQ(700l, result);
}
#endif /* TESTREPAYLOAN_H */

