#ifndef TRADESTATISTICS_H
#define TRADESTATISTICS_H

#include "Huobi/Decimal.h"

namespace Huobi {

    /**
     * The summary of trading in the market for the last 24 hours.
     */
    struct TradeStatistics {
        /**
         * The UNIX formatted timestamp generated by server in UTC.
         */
        long timestamp;

        /**
         * The opening price of last 24 hours.
         */
        Decimal open;

        /**
         * The last price of last 24 hours.
         */
        Decimal close;

        /**
         * The aggregated trading volume in USDT.
         */
        Decimal amount;

        /**
         * The high price of last 24 hours.
         */
        Decimal high;

        /**
         * The low price of last 24 hours.
         */
        Decimal low;

        /**
         * The number of completed trades.
         */
        long count;

        /**
         * The trading volume in base currency of last 24 hours.
         */
        Decimal volume;

        TradeStatistics(com::huobi::gateway::MarketSummary sum) {

            timestamp = sum.ts();

            open = Decimal(sum.open().c_str());

            close = Decimal(sum.close().c_str());

            amount = Decimal(sum.turnover().c_str());

            high = Decimal(sum.high().c_str());

            low = Decimal(sum.low().c_str());

            count = sum.num_of_trades();

            volume = Decimal(sum.volume().c_str());
        }

        TradeStatistics() {
        }
    };
}


#endif /* TRADESTATISTICS_H */

