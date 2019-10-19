#include "WebSocketWatchDog.h"

#include <chrono>
#include "WebSocketConnection.h"

namespace Huobi {

    class AutoLock {
    public:

        AutoLock(std::mutex& mutex) : mutex_(mutex) {
            mutex_.lock();
        }

        ~AutoLock() {
            mutex_.unlock();
        }
    private:
        std::mutex& mutex_;
    };

    void WebSocketWatchDog::WatchDogThread() {
        while (1) {
            AutoLock lock(mutex);
            for (std::list<WebSocketConnection*>::iterator it = connectionList.begin(); it != connectionList.end(); ++it) {
                WebSocketConnection* connection = *it;
                // Check response

                if (connection->getConnectState() == ConnectionStateEnum::CONNECTED) {
                    lwsl_user("time....\n");
                    time_t ts = TimeService::getCurrentTimeStamp() - connection->getLastReceivedTime();
                    if (ts > receiveLimitMs) {
                        Logger::WriteLog(" No response from server");
                        lwsl_user("auto recon\n");
                        connection->reConnect(connectionDelayOnFailure);
                    }
                } else if (connection->getConnectState() == ConnectionStateEnum::CLOSED_ON_ERROR) {
                    lwsl_user("check close, try reconnect...\n");
                    connection->reConnect(connectionDelayOnFailure);
                } else if (connection->getConnectState() == ConnectionStateEnum::DELAY_CONNECT) {
                    connection->reConnect();
                }

            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }

    void WebSocketWatchDog::onConnectionCreated(WebSocketConnection* connection) {
        std::list<WebSocketConnection*>::iterator conit = connectionList.begin();
        for (; conit != connectionList.end(); conit++) {
            if (*conit == connection)
                return;
        }
        connectionList.push_back(connection);
    }

    void WebSocketWatchDog::onClosedNormally(WebSocketConnection* connection) {
        connectionList.remove(connection);
    }

    WebSocketWatchDog::WebSocketWatchDog() {

        dogthread = std::thread(&WebSocketWatchDog::WatchDogThread);

    }
    WebSocketWatchDog* WebSocketWatchDog::dog = new WebSocketWatchDog();

    int WebSocketWatchDog::receiveLimitMs = 60000;

    int WebSocketWatchDog::connectionDelayOnFailure = 15;

    std::list<WebSocketConnection*> WebSocketWatchDog::connectionList;
    std::mutex WebSocketWatchDog::mutex;
}


