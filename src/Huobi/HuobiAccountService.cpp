/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "HuobiAccountService.h"
#include "../Huobi/parser/account/AccountParser.h"
namespace Huobi {

    std::vector<Account> HuobiAccountService::getAccounts() {
        UrlParamsBuilder builder;
        JsonWrapper json = restConnection->executeGetWithSignature(GET_ACCOUNTS_PATH, builder);
        printf("after executeGetWithSignature\n");
        JsonWrapper data = json.getJsonObjectOrArray("data");
        //解析数据
        printf("解析数据\n");
        std::vector<Account> accounts = AccountParser::parseArray(data);
         printf("after 解析数据\n");
        return accounts;
    }


}