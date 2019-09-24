#ifndef SUBSCRIPTIONOPTIONS_H
#define SUBSCRIPTIONOPTIONS_H

#include <string>
#include <memory>
namespace Huobi {
    
    struct SubscriptionOptions {
        SubscriptionOptions() {}
        
        SubscriptionOptions(const SubscriptionOptions& op)
        : isAutoReconnect (op.isAutoReconnect)
        , receiveLimitMs(op.receiveLimitMs)
        , connectionDelayOnFailure(op.connectionDelayOnFailure)
        , url(op.url) {
        }
        /**
         * flag of reconnect
         */
        bool isAutoReconnect = true;
        /**
         * receiving timeout limit,in milliseconds
         */
        int receiveLimitMs = 60000;

        /**
         * connection failed delay time, in seconds
         */
       int connectionDelayOnFailure = 15;
       /*
        *support set url by user
        */
       std::string url = "https://api.huobi.pro";

    };

    typedef std::shared_ptr<SubscriptionOptions> SubscriptionOptionsHandler;
}

#endif /* SUBSCRIPTIONOPTIONS_H */

