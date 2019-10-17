///*
// * To change this license header, choose License Headers in Project Properties.
// * To change this template file, choose Tools | Templates
// * and open the template in the editor.
// */
//
///* 
// * File:   FeeRate.h
// * Author: yuanxueqi
// *
// * Created on 2019年9月10日, 下午6:20
// */
//
//#ifndef FEERATE_H
//#define FEERATE_H
//
//namespace Huobi {
//
//    /**
//     * The current fee of taker and maker.
//     */
//    struct FeeRate {
//        /**
//         * The symbol like "btcusdt".
//         */
//        std::string symbol;
//
//        /**
//         * The fee of maker.
//         */
//        Decimal maker_fee;
//        /**
//         * The fee of taker.
//         */
//        Decimal taker_fee;
//
//        static RestApiJsonParser<std::vector<FeeRate> > getDataParser() {
//            RestApiJsonParser<std::vector < FeeRate>> res;
//            res.parseJson = [](JsonWrapper json) {
//                std::vector<FeeRate> feeRatelList;
//                JsonWrapper dataArray = json.getJsonObjectOrArray("data");
//                for (int i = 0; i < dataArray.size(); i++) {
//                    JsonWrapper itemInData = dataArray.getJsonObjectAt(i);
//                    FeeRate feeRate = parse(itemInData);
//                    feeRatelList.push_back(feeRate);
//                }
//                return feeRatelList;
//            };
//            return res;
//        }
//
//        static FeeRate parse(JsonWrapper itemInData) {
//            FeeRate feeRate;
//            feeRate.symbol = itemInData.getString("symbol");
//            feeRate.maker_fee = itemInData.getDecimal("maker-fee");
//            feeRate.taker_fee = itemInData.getDecimal("taker-fee");
//            return feeRate;
//        }
//    };
//
//
//}
//
//#endif /* FEERATE_H */
//
