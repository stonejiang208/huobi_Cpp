//#ifndef LOAN_H
//#define LOAN_H
//
//#include <string>
//#include "Huobi/Enums.h"
//#include "Decimal.h"
//#include "/root/huobi_Cpp/src/AccountsInfoMap.h"
//
//namespace Huobi {
//
//    /**
//     * The margin order information.
//     */
//    struct Loan {
//        /**
//         * The order id.
//         */
//        long id = 0;
//
//        /**
//         * The user id.
//         */
//        long userId = 0;
//
//        /**
//         * The account type which created the loan order.
//         */
//        AccountType accountType;
//
//        /**
//         * The symbol, like "btcusdt".
//         */
//        std::string symbol;
//
//        /**
//         * The currency name.
//         */
//        std::string currency;
//
//        /**
//         * The amount of the origin loan.
//         */
//        Decimal loanAmount;
//
//        /**
//         * The amount of the loan left.
//         */
//        Decimal loanBalance;
//
//        /**
//         * The loan interest rate.
//         */
//        Decimal interestRate;
//
//        /**
//         * The accumulated loan interest.
//         */
//        Decimal interestAmount;
//
//        /**
//         * The amount of loan interest left.
//         */
//        Decimal interestBalance;
//
//        /**
//         * The loan stats, possible values: created, accrual, cleared, invalid.
//         */
//        LoanOrderStates state;
//
//        /**
//         * The UNIX formatted timestamp in UTC when the order was created.
//         */
//        long createdTimestamp = 0;
//
//        /**
//         * The UNIX formatted timestamp in UTC when the last accrue happened.
//         */
//        long accruedTimestamp = 0;
//
//        static RestApiJsonParser<std::vector<Loan> > getDataParser(std::string accessKey) {
//            RestApiJsonParser<std::vector < Loan>> res;
//            res.parseJson = [accessKey](JsonWrapper json) {
//                std::vector<Loan> loans;
//                JsonWrapper data = json.getJsonObjectOrArray("data");
//                for (int i = 0; i < data.size(); i++) {
//                    JsonWrapper item = data.getJsonObjectAt(i);
//                    Loan loan = parse(item, accessKey);
//                    loans.push_back(loan);
//                }
//                return loans;
//            };
//            return res;
//        }
//
//        static Loan parse(JsonWrapper item, std::string accessKey) {
//            Loan loan;
//            loan.loanBalance = item.getDecimal("loan-balance");
//            loan.interestBalance = item.getDecimal("interest-balance");
//            loan.interestRate = item.getDecimal("interest-rate");
//            loan.loanAmount = item.getDecimal("loan-amount");
//            loan.interestAmount = item.getDecimal("interest-amount");
//            loan.symbol = item.getString("symbol");
//            loan.currency = item.getString("currency");
//            loan.id = item.getLong("id");
//            loan.state = LoanOrderStates::lookup(item.getString("state"));
//            loan.accountType = AccountsInfoMap::getAccount(accessKey, item.getLong("account-id")).type;
//            loan.userId = item.getLong("user-id");
//            loan.accruedTimestamp =
//                    TimeService::convertCSTInMillisecondToUTC(item.getLong("accrued-at"));
//            loan.createdTimestamp =
//                    TimeService::convertCSTInMillisecondToUTC(item.getLong("created-at"));
//            return loan;
//        }
//    };
//}
//
//
//#endif /* LOAN_H */
//
