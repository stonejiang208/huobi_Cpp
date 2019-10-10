#ifndef TRADE_H
#define TRADE_H

#include<string>
#include "Enums.h"
#include "/root/huobi_Cpp/src/TimeService.h"
#include "/root/huobi_Cpp/src/RestApiJsonParser.h"
#include "/root/huobi_Cpp/src/Utils/JsonWrapper.h"
#include "Huobi/Decimal.h"
#include <vector>
namespace Huobi {

    /**
     * The trade information with price and amount etc.
     */
    struct Trade {
        /**
         * The unique trade id of this trade.
         */
        std::string tradeId;

        /**
         * The UNIX formatted timestamp generated by server in UTC.
         */
        long timestamp;

        /**
         * The trading price in quote currency.
         */
        Decimal price;

        /**
         * The trading volume in base currency.
         */
        Decimal amount;

        /**
         * The direction of the taker trade: 'buy' or 'sell'.
         */
        TradeDirection direction;

        static RestApiJsonParser<std::vector<Trade> > getDataParser() {

            RestApiJsonParser<std::vector < Trade>> res;
            res.parseJson = [](JsonWrapper json) {
                std::vector<Trade> trades;
                JsonWrapper dataArray = json.getJsonObjectOrArray("data");
                for (int i = 0; i < dataArray.size(); i++) {
                    JsonWrapper item = dataArray.getJsonObjectAt(i);
                    JsonWrapper dataArrayIn = item.getJsonObjectOrArray("data");
                    for (int j = 0; j < dataArrayIn.size(); j++) {
                        JsonWrapper itemIn = dataArrayIn.getJsonObjectAt(j);
                        Trade trade = parse(itemIn);
                        trades.push_back(trade);
                    }
                }
                return trades;
            };
            return res;
        }

        static Trade parse(JsonWrapper item) {
            Trade trade;
            trade.price = item.getDecimal("price");
            trade.amount = item.getDecimal("amount");
            trade.tradeId = item.getString("id");
            trade.timestamp = TimeService::convertCSTInMillisecondToUTC(item.getLong("ts"));
            trade.direction = TradeDirection::lookup(item.getString("direction"));
            return trade;
        }
    };
}
#endif /* TRADE_H */

