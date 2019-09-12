/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WebSocketsContext.h
 * Author: U0151316
 *
 * Created on September 11, 2019, 11:32 AM
 */

#ifndef WEBSOCKETSCONTEXT_H
#define WEBSOCKETSCONTEXT_H

#include "../WebSocketRequest.h"
#include "../WebSocketConnection.h"
#include <boost/asio/io_context.hpp>

namespace Huobi {

    class WebSocketsService {
    public:

        WebSocketsService() : ssl_(boost::asio::ssl::context::sslv23_client) {
            ssl_.load_verify_file("/etc/huobi_cert/cert.pem");
        };
    private:
        WebSocketsService(const WebSocketsService& orig);

        ~WebSocketsService() {
        };

    public:

        void startService() {
            // Run the I/O service. The call will return when
            // the socket is closed.
            io_.run();
        }

        void stopService() {
            io_.stop();
        }

        //        void createConnection(WebSocketRequest* request) {
        //            
        //        }

        boost::asio::io_context& getIO() {
            return io_;
        };

        boost::asio::ssl::context& getSSL() {
            return ssl_;
        };
    private:
        boost::asio::io_context io_;
        boost::asio::ssl::context ssl_;
    };
}


#endif /* WEBSOCKETSCONTEXT_H */

