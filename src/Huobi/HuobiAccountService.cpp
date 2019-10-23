/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "HuobiAccountService.h"
#include "../Huobi/parser/account/AccountParser.h"
#include "../Huobi/parser/account/AccountBalanceParser.h"
#include "../Huobi/parser/account/SubuserAggregateBalanceParser.h"
#include "../../src/Utils/InputChecker.h"
#include "../../src/Utils/SymbolUtils.h"
#include "../Huobi/parser/account/AccountChangeEventParser.h"
namespace Huobi {

    std::vector<Account> HuobiAccountService::getAccounts() {
        UrlParamsBuilder builder;
        JsonWrapper json = restConnection->executeGetWithSignature(GET_ACCOUNTS_PATH, builder);

        JsonWrapper data = json.getJsonObjectOrArray("data");
        //解析数据

        std::vector<Account> accounts = AccountParser::parseArray(data);

        return accounts;
    }

    AccountBalance HuobiAccountService::getAccountBalance(const AccountBalanceRequest& request) {
        InputChecker::checker()
                ->shouldBiggerThanZero(request.accountId, "accountId");
        std::string topic = GET_ACCOUNT_BALANCE_PATH;
        topic.replace(topic.find("{account-id}"), 12, std::to_string(request.accountId));
        UrlParamsBuilder builder;
        JsonWrapper json = restConnection->executeGetWithSignature(topic.c_str(), builder);

        JsonWrapper data = json.getJsonObjectOrArray("data");
        AccountBalance accountBalance = AccountBalanceParser::parse(data);
        return accountBalance;
    }

    long HuobiAccountService::transferSubuser(const TransferSubuserRequest& request) {

        InputChecker::checker()
                ->shouldBiggerThanZero(request.subUid, "sub-uid")
                ->shouldNotNull(request.currency, "currency")
                ->shouldBiggerThanZero(request.amount, "amount")
                ->checkEnumNull(request.type);


        UrlParamsBuilder builder;
        builder.putPost("sub-uid", request.subUid);
        builder.putPost("currency", request.currency);
        builder.putPost("amount", request.amount);
        builder.putPost("type", request.type.getValue());

        JsonWrapper json = restConnection->executePostWithSignature(TRANSFER_SUBUSER_PATH, builder);
        return json.getLong("data");
    }

    std::vector<AccountBalance> HuobiAccountService::getSubuserAccountBalance(long subuserId) {


        InputChecker::checker()
                ->shouldBiggerThanZero(subuserId, "subId");
        std::string topic = GET_SUBUSER_ACCOUNT_BALANCE_PATH;
        topic.replace(topic.find("{sub-uid}"), 9, std::to_string(subuserId));
        UrlParamsBuilder builder;
        JsonWrapper json = restConnection->executeGetWithSignature(topic.c_str(), builder);
        JsonWrapper data = json.getJsonObjectOrArray("data");
        std::vector<AccountBalance> accountsBalance = AccountBalanceParser::parseArray(data);
        return accountsBalance;
    }

    std::vector<SubuserAggregateBalance> HuobiAccountService::getSubuserAggregateBalance() {
        UrlParamsBuilder builder;
        JsonWrapper json = restConnection->executeGetWithSignature(GET_SUBUSER_AGGREGATE_BALANCE_PATH, builder);
        JsonWrapper data = json.getJsonObjectOrArray("data");
        std::vector<SubuserAggregateBalance>subuserAggregateBalances = SubuserAggregateBalanceParser::parseArray(data);
        return subuserAggregateBalances;
    }

    void HuobiAccountService::subAccounts(const SubAccountChangeRequest& request, const std::function<void( const AccountChangeEvent&) > callback) {
       
        std::list<std::string> commandList;
//        JsonWriter writer;
//        writer.put("op", "sub");
//        writer.put("cid", std::to_string(TimeService::getCurrentTimeStamp()));
//        writer.put("topic", "accounts");
//        if (!request.balanceMode.isNull())
//            writer.put("model", request.balanceMode.getValue());
//        commandList.push_back(writer.toJsonString());
        HuobiWebSocketConnection<AccountChangeEvent>::createAssetConnection(commandList, callback, options, AccountChangeEventParser::parse);


    }

}