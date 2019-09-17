#ifndef WEBSOCKETWATCHDOG_H
#define WEBSOCKETWATCHDOG_H
#include <list>
#include <thread>
#include <mutex>
#include "TimeService.h"
#include "Huobi/SubscriptionOptions.h"
#include "WebSocketConnection.h"


namespace Huobi {

    class WebSocketsService;
     
    class WebSocketWatchDog {
    private:
        SubscriptionOptions op_;
        
    public:   
        typedef std::list<WebSocketConnectHanlder> WebSocketConnectList;
        
        WebSocketWatchDog(WebSocketsService* service);
        void WatchDogThread();
        bool isRunning() const{ return runningFlag; }
        void onConnectionCreated(WebSocketConnectHanlder connection);
        void onClosedNormally(WebSocketConnectHanlder connection);

        
    private:
        WebSocketConnectList connectionList_;
        WebSocketsService* service_;
        std::mutex mutex;
        bool runningFlag;
        std::thread dogthread;
    };
}


#endif /* WEBSOCKETWATCHDOG_H */
