/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SDKException.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月16日, 下午5:52
 */

#ifndef SDKEXCEPTION_H
#define SDKEXCEPTION_H


#include <string>

namespace Huobi {

    class SDKException {
    public:
        std::string errorCode;
        std::string errorMsg;
    public:
        static std::string RUNTIME_ERROR;
        static std::string INPUT_ERROR;
        static std::string KEY_MISSING;
        static std::string SYS_ERROR;
        static std::string SUBSCRIPTION_ERROR;
        static std::string ENV_ERROR;
        static std::string EXEC_ERROR;
   

        SDKException(std::string code, std::string msg) {
            errorCode = code;
            errorMsg = msg;
        }

        SDKException() {

        }
    };
}



#endif /* SDKEXCEPTION_H */

