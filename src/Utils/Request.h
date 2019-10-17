/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Request.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月16日, 下午4:02
 */

#ifndef REQUEST_H
#define REQUEST_H

#include "../Utils/JsonWrapper.h"
namespace Huobi {

    class Request {
    private:
        std::string postbody;
        std::string url;

    public:
        std::string method;

        const std::string& getUrl() const {
            return url;
        }

        void setUrl(std::string url) {
            this->url = url;
        }

        std::string getPostBody() const {
            return postbody;
        }

        void setPostBody(std::string json) {
            this->postbody = json;
        }

    };

}

#endif /* REQUEST_H */

