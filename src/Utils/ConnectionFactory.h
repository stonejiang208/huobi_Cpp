/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ConnectionFactory.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月16日, 下午3:57
 */

#ifndef CONNECTIONFACTORY_H
#define CONNECTIONFACTORY_H

#include <curl/curl.h>
#include "Request.h"
#include "../exception/SDKException.h"
namespace Huobi{

    class ConnectionFactory{
    public:
         static size_t writeFun(void *input, size_t uSize, size_t uCount, void *avg) {
            size_t uLen = uSize*uCount;
            std::string &sBuffer = *reinterpret_cast<std::string *> (avg);
            sBuffer.append(reinterpret_cast<const char *> (input), uLen);
            return uLen;
        }
        
      static std::string execute(Request* request) {
                    std::unique_ptr<Request > ptr(request);
                    CURLcode code = curl_global_init(CURL_GLOBAL_DEFAULT);
                    if (code != CURLE_OK) {
                        std::cout << "curl_global_init() Err" << std::endl;
                        throw SDKException("", "curl_global_init() Err");
                    }
                    CURL* pCurl = curl_easy_init();
                    if (pCurl == NULL) {
                        std::cout << "curl_easy_init() Err" << std::endl;
                        throw SDKException("", "curl_easy_init() Err");
                    }
                    std::string sBuffer;
                    printf("\n");
                    printf("------request------\n");
                    printf(ptr->getUrl().c_str());
                    printf("\n");
                    curl_easy_setopt(pCurl, CURLOPT_SSLKEYTYPE, "PEM");
                    curl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYPEER, 1L);
                    curl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYHOST, 1L);
                    curl_easy_setopt(pCurl, CURLOPT_URL, request->getUrl().c_str()); // 访问的URL
                    curl_easy_setopt(pCurl, CURLOPT_CAINFO, "/etc/huobi_cert/cert.pem");
                    if (ptr->method == "POST") {
                        curl_easy_setopt(pCurl, CURLOPT_POST, 1);
                        curl_slist *plist = curl_slist_append(NULL, "Content-Type:application/json;charset=UTF-8");
                        curl_easy_setopt(pCurl, CURLOPT_HTTPHEADER, plist);
                    } else {
                        curl_slist *plist = curl_slist_append(NULL, "Content-Type:application/x-www-form-urlencoded");
                        curl_easy_setopt(pCurl, CURLOPT_HTTPHEADER, plist);
                    }
                    curl_easy_setopt(pCurl, CURLOPT_TIMEOUT, 20); // 超时(单位S)
                    curl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, &writeFun); // !数据回调函数
                    curl_easy_setopt(pCurl, CURLOPT_WRITEDATA, &sBuffer); // !数据回调函数的参，一般为Buffer或文件fd
                    if (request->method == "POST") {                      
                        curl_easy_setopt(pCurl, CURLOPT_POSTFIELDS, request->getPostBody().c_str());
                    }
                    curl_easy_perform(pCurl);
                    if (code != CURLE_OK) {
                        std::cout << "curl_easy_perform() Err" << std::endl;
                        throw SDKException("", "curl_easy_perform() Err");
                    }
                    printf("------response------\n");
                    printf(sBuffer.c_str());
                    printf("\n");
       
                    curl_easy_cleanup(pCurl);
                    curl_global_cleanup();
                
                    return sBuffer;
                }
    };
}

#endif /* CONNECTIONFACTORY_H */

