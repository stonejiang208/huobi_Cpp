#ifndef WEBSOCKETWATCHDOG_H
#define WEBSOCKETWATCHDOG_H
#include <list>
#include <thread>
#include <mutex>
#include "TimeService.h"
#include "Huobi/SubscriptionOptions.h"
#include "WebSocketConnection.h"


namespace Huobi {

    class WebSocketWatchDog {
    private:
        SubscriptionOptionsHandler op_;
        
    public:   
        typedef std::list<WebSocketConnectHanlder> WebSocketConnectList;
        
        WebSocketWatchDog(const SubscriptionOptionsHandler& op);
        void WatchDogThread();
        bool isRunning() const{ return runningFlag; }
        void onConnectionCreated(WebSocketConnectHanlder connection);
        void onClosedNormally(WebSocketConnectHanlder connection);

        
    private:
        WebSocketConnectList connectionList_;
        std::mutex mutex;
        bool runningFlag;
        std::thread dogthread;
    };
    
    typedef std::shared_ptr<WebSocketWatchDog> WebSocketWatchDogHandler;
}


#endif /* WEBSOCKETWATCHDOG_H */
