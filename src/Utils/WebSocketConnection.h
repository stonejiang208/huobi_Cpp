/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WebSocketConnection.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月18日, 下午3:02
 */

#ifndef WEBSOCKETCONNECTION_H
#define WEBSOCKETCONNECTION_H
#include <memory>
#include <list>
#include <string>
#include <libwebsockets.h>
#include <mutex>
#include "constant/enums.h"
namespace Huobi {

    struct WebSocketConnection {
       virtual void onOpen(lws* ws) = 0;
       virtual void onMessage(const char* message,size_t len) = 0;
       virtual void disconnect() = 0;
        virtual ConnectionStateEnum getConnectState() = 0;

virtual bool send() = 0;
       virtual long getLastReceivedTime() = 0;
       virtual void reConnect() = 0;
virtual void reConnect(int delay) = 0;
    };

}

#endif /* WEBSOCKETCONNECTION_H */

