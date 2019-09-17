#include "WebSocketWatchDog.h"

#include <list>
#include <chrono>
#include <thread>
#include "WebSocketConnection.h"
#include "WebSockets/WebSocketsService.h"

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
        while (runningFlag) {
            AutoLock lock(mutex);
            for (WebSocketConnectList::iterator it = connectionList_.begin(); it != connectionList_.end(); ++it) {
                std::shared_ptr<WebSocketConnection> connection = *it;
                LineStatus lineStatus = connection->getLineStatus();
                if (lineStatus == LineStatus::LINE_CONNECTED) {
                    // Check response
                    time_t ts = TimeService::getCurrentTimeStamp() - connection->getLastReceivedTime();
                    if (ts > op_.receiveLimitMs) {
                        Logger::LogWarning("No response from server");
                        connection->reConnect(op_.connectionDelayOnFailure);
                    }
                } else if (lineStatus == LineStatus::LINE_CLOSED_ON_ERROR) {
                    connection->reConnect(op_.connectionDelayOnFailure);
                } else if (lineStatus == LineStatus::LINE_DELAY) {
                    connection->reConnect();
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }

    void WebSocketWatchDog::onConnectionCreated(WebSocketConnectHanlder connection) {
        WebSocketConnectList::iterator it = connectionList_.begin();
        for (; it != connectionList_.end(); it++) {
            if (*it == connection)
                return;
        }
        connectionList_.push_back(connection);
    }

    void WebSocketWatchDog::onClosedNormally(WebSocketConnectHanlder connection) {
        connectionList_.remove(connection);
    }

    WebSocketWatchDog::WebSocketWatchDog(WebSocketsService* service) : runningFlag(true) {
        service_ = service;
        if (service_->getOptions().isAutoReconnect) {
            dogthread = std::thread(&WebSocketWatchDog::WatchDogThread, this);
        }
    }

}


