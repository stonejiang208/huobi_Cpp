/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RestApiJsonParser.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月8日, 下午5:49
 */

#ifndef RESTAPIJSONPARSER_H
#define RESTAPIJSONPARSER_H
#include <functional>
#include "Utils/JsonWrapper.h"
namespace Huobi {

    template <typename T>
    class RestApiJsonParser {
    public:
        std::function<T(const JsonWrapper&) > parseJson;
    };



}

#endif /* RESTAPIJSONPARSER_H */

