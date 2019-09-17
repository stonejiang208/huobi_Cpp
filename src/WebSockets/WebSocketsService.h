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
#include "../WebSocketWatchDog.h"
#include <boost/asio/io_context.hpp>

namespace Huobi {

    typedef std::shared_ptr<WebSocketsService> WebSocketsServiceHanlder;

    class WebSocketsService {
    public:
        typedef std::list<WebSocketConnectHanlder> WebSocketConnectList;

        WebSocketsService()
        : ssl_(boost::asio::ssl::context::sslv23_client) {
            ssl_.load_verify_file("/etc/huobi_cert/cert.pem");
            watchDog_ = new WebSocketWatchDog(this);
        };

        ~WebSocketsService() {
        };
    private:
        WebSocketsService(const WebSocketsService& orig);

    public:

        void initialize(const std::string& apiKey, const std::string& secretKey, const SubscriptionOptions op) {
            apiKey_ = apiKey;
            secretKey_ = secretKey;
            op_ = op;
        }

        void startService() {
            WebSocketConnectList::iterator it = connectionList_.begin();
            for (; it != connectionList_.end(); ++it) {
                (*it)->connect();
            }
            // Run the I/O service. The call will return when
            // the socket is closed.
            io_.run();
        }

        void stopService() {
            WebSocketConnectList::iterator it = connectionList_.begin();
            for (; it != connectionList_.end(); ++it) {
                (*it)->close();
            }
            io_.stop();
        }

        void createConnection(WebSocketRequest* request) {
            auto connection = std::make_shared<WebSocketConnection>(
                    request, this);
            connectionList_.push_back(connection);
        }

        boost::asio::io_context& getIO() {
            return io_;
        };

        boost::asio::ssl::context& getSSL() {
            return ssl_;
        };

        const SubscriptionOptions& getOptions() {
            return op_;
        }

        const WebSocketConnectList& getConnectionList() const {
            return connectionList_;
        }
        
        const std::string& getApiKey() const {
            return apiKey_;
        }

        const std::string& getSecretKey() const {
            return secretKey_;
        }

    private:
        boost::asio::io_context io_;
        boost::asio::ssl::context ssl_;
        WebSocketConnectList connectionList_;
        WebSocketWatchDog* watchDog_ = nullptr;
        
        SubscriptionOptions op_;
        std::string apiKey_;
        std::string secretKey_;
        std::string host_;
    };
}


#endif /* WEBSOCKETSCONTEXT_H */

