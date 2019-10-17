//#ifndef ETFSWAPCONFIG_H
//#define ETFSWAPCONFIG_H
//
//#include <vector>
//
//#include "Huobi/Enums.h"
//#include "Huobi/Decimal.h"
//#include "Huobi/UnitPrice.h"
//
//namespace Huobi {
//
//    /*
//     * The basic information of ETF creation and redemption, as well as ETF constituents, including max
//     * amount of creation, min amount of creation, max amount of redemption, min amount of redemption,
//     * creation fee rate, redemption fee rate, eft create/redeem status.
//     */
//    struct EtfSwapConfig {
//        /**
//         * The minimum creation amounts per request.
//         */
//        int purchaseMinAmount = 0;
//
//        /**
//         * The max creation amounts per request.
//         */
//        int purchaseMaxAmount = 0;
//
//        /**
//         * The minimum redemption amounts per request.
//         */
//        int redemptionMinAmount = 0;
//
//        /**
//         * The max redemption amounts per request.
//         */
//        int redemptionMaxAmount = 0;
//
//        /**
//         * The creation fee rate.
//         */
//        Decimal purchaseFeeRate;
//
//        /**
//         * The redemption fee rate.
//         */
//        Decimal redemptionFeeRate;
//
//        /**
//         * The status of the ETF.
//         */
//        EtfStatus status;
//
//        /**
//         * ETF constitution in format of amount and currency.
//         */
//        std::vector<UnitPrice> unitPriceList;
//
//        static RestApiJsonParser<EtfSwapConfig > getDataParser() {
//            RestApiJsonParser<EtfSwapConfig> res;
//            res.parseJson = [](JsonWrapper json) {
//                JsonWrapper data = json.getJsonObjectOrArray("data");
//                EtfSwapConfig etfSwapConfig = parse(data);
//                return etfSwapConfig;
//            };
//            return res;
//        }
//
//        static EtfSwapConfig parse(JsonWrapper data) {
//            EtfSwapConfig etfSwapConfig;
//            etfSwapConfig.purchaseMaxAmount = data.getInt("purchase_max_amount");
//            etfSwapConfig.purchaseMinAmount = data.getInt("purchase_min_amount");
//            etfSwapConfig.redemptionMaxAmount = data.getInt("redemption_max_amount");
//            etfSwapConfig.redemptionMinAmount = data.getInt("redemption_min_amount");
//            etfSwapConfig.purchaseFeeRate = data.getDecimal("purchase_fee_rate");
//            etfSwapConfig.redemptionFeeRate = data.getDecimal("redemption_fee_rate");
//            etfSwapConfig.status =
//                    EtfStatus::lookup(std::to_string(data.getInt("etf_status")));
//            std::vector<UnitPrice> unitPriceList = UnitPrice::getParser("unit_price").parseJson(data);
//            etfSwapConfig.unitPriceList = unitPriceList;
//            return etfSwapConfig;
//        }
//    };
//}
//
//
//#endif /* ETFSWAPCONFIG_H */
//
