/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HuobiRestConnection.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月15日, 下午6:56
 */

#ifndef HUOBIRESTCONNECTION_H
#define HUOBIRESTCONNECTION_H

#include <memory>
#include "../../../src/Utils/ConnectionFactory.h"
#include "../../../src/Utils/JsonDocument.h"
#include "../../exception/SDKException.h"
#include "../../options/HuobiOptions.h"
#include "../../Utils/UrlParamsBuilder.h"
#include "../../EtfResult.h"
#include "/root/huobi_Cpp/src/Utils/JsonWrapper.h"
#include "../../Utils/ApiSignature.h"
#include "../../Utils/GetHost.h"
namespace Huobi {

    class HuobiRestConnection {
    private:
        HuobiOptions options;
    public:

        HuobiRestConnection(HuobiOptions options) {
            this->options = options;
        }

        void checkResponse(const JsonWrapper& json) {
            try {
                if (json.containKey("status")) {
                    std::string status = json.getString("status");
                    if ("error" == status) {
                        std::string err_code = json.getString("err-code");
                        std::string err_msg = json.getString("err-msg");
                        throw SDKException(SDKException::EXEC_ERROR,
                                "[Executing] " + err_code + ": " + err_msg);
                    } else if ("ok" != status) {
                        throw SDKException(
                                SDKException::RUNTIME_ERROR, "[Invoking] Response is not expected: " + status);
                    }
                } else if (json.containKey("success")) {
                    bool success = json.getBool("success");
                    if (!success) {
                        std::string err_code = EtfResult::checkResult(json.getInt("code"));
                        std::string err_msg = json.getString("message");
                        if (err_code.empty()) {
                            throw SDKException(SDKException::EXEC_ERROR, "[Executing] " + err_msg);
                        } else {
                            throw SDKException(SDKException::EXEC_ERROR,
                                    "[Executing] " + err_code + ": " + err_msg);
                        }
                    }
                } else {
                    throw SDKException(
                            SDKException::RUNTIME_ERROR, "[Invoking] Status cannot be found in response.");
                }
            } catch (std::exception e) {
                std::string msg;
                msg = "[Invoking] Unexpected error: ";
                throw SDKException(
                        SDKException::RUNTIME_ERROR, msg + e.what());
            }
        }

        JsonWrapper executeGet(const char* adress, UrlParamsBuilder&builder) {
            //创建请求体
            Request* res = new Request();
            res->method = "GET";
            std::string url;
            if (builder.getAdress() == "") {
                url = adress;
            } else {
                builder.getAdress();
                std::string sadress = adress;
                url = sadress + "?" + builder.getAdress();
            }
            builder.setAdress(url);
            res->setUrl(options.restHost + builder.getAdress());
            //  res->setPostBody(builder.getPostBody());
            //执行连接,返回内容
            std::string sBuffer = ConnectionFactory::execute(res);
            //             std::cout<<"sbuffer:"<<std::endl;
            //            std::cout<<sBuffer<<std::endl;
            JsonDocument* djson = new JsonDocument();
            JsonWrapper json = djson->parseFromString(sBuffer.c_str());
            //检查响应体         

            checkResponse(json);

            //  delete res;

            return json;

        }

        JsonWrapper executeGetWithSignature(const char* adress, UrlParamsBuilder&builder) {
            //创建请求体

            Request* res = new Request();
            res->method = "GET";

            std::string temp = adress;
            temp += "?";

            std::string tail = ApiSignature::buildSignaturePath(GetHost(options.restHost), options.apiKey, options.secretKey,
                    adress, res->method, builder.getAdress().c_str());
            if (builder.getAdress().empty()) {
                builder.setAdress(temp + builder.getAdress() + tail);
            } else {
                builder.setAdress(temp + builder.getAdress() + "&" + tail);
            }

            res->setUrl(options.restHost + builder.getAdress());

            //执行连接,返回内容
            std::string sBuffer = ConnectionFactory::execute(res);

            JsonDocument* djson = new JsonDocument();
            JsonWrapper json = djson->parseFromString(sBuffer.c_str());
            
            //检查响应体         
            checkResponse(json);
            printf("checkResponse\n");
            return json;

        }




    };
}


#endif /* HUOBIRESTCONNECTION_H */

