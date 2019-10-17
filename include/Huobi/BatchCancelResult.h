//#ifndef BATCHCANCELRESULT_H
//#define BATCHCANCELRESULT_H
//
//namespace Huobi {
//
//    /**
//     * The result of batch cancel operation.
//     */
//    struct BatchCancelResult {
//        /**
//         * The number of cancel request sent successfully.
//         */
//        int successCount = 0;
//
//        /**
//         * The number of cancel request failed.
//         */
//        int failedCount = 0;
//
//        static RestApiJsonParser<BatchCancelResult > getDataParser() {
//            RestApiJsonParser<BatchCancelResult> res;
//            res.parseJson = [](JsonWrapper json) {
//                BatchCancelResult batchCancelResult = parse(json);
//                return batchCancelResult;
//            };
//            return res;
//        }
//
//        static BatchCancelResult parse(JsonWrapper json) {
//            BatchCancelResult batchCancelResult;
//            JsonWrapper data = json.getJsonObjectOrArray("data");
//            batchCancelResult.successCount = data.getInt("success-count");
//            batchCancelResult.failedCount = data.getInt("failed-count");
//            return batchCancelResult;
//        }
//    };
//
//}
//
//
//#endif /* BATCHCANCELRESULT_H */
//
