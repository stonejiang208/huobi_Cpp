#ifndef WEBSOCKETWATCHDOG_H
#define WEBSOCKETWATCHDOG_H
#include <list>
#include <thread>
#include <mutex>
#include "TimeService.h"
//#include "Huobi/SubscriptionOptions.h"
#include "constant/Logger.h"

namespace Huobi {

    class WebSocketConnection;

    class WebSocketWatchDog {
    public:
        /**
         * receiving timeout limit,in milliseconds
         */
        static int receiveLimitMs;

        /**
         * connection failed delay time, in seconds
         */
        static int connectionDelayOnFailure;

        //  WebSocketWatchDog(SubscriptionOptions &op);
        static void WatchDogThread();

        static void onConnectionCreated(WebSocketConnection* connection);
        static void onClosedNormally(WebSocketConnection* connection);
        static WebSocketWatchDog* dog;

        static std::list<WebSocketConnection*> connectionList;
        static std::mutex mutex;

        ~WebSocketWatchDog() {
            dogthread.join();
        }
    private:

        // bool runningFlag;
        std::thread dogthread;
        WebSocketWatchDog();

    };
}


#endif /* WEBSOCKETWATCHDOG_H */
