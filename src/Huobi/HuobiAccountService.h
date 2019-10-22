/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HuobiAccountService.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月22日, 下午6:57
 */

#ifndef HUOBIACCOUNTSERVICE_H
#define HUOBIACCOUNTSERVICE_H


#include "client/AccountClient.h"
#include "connection/HuobiRestConnection.h"
#include "connection/HuobiWebSocketConnection.h"

#include "../Utils/InputChecker.h"

#include "../options/HuobiOptions.h"


namespace Huobi {

    class HuobiAccountService : public AccountClient {
    private:
        HuobiRestConnection* restConnection;
        HuobiOptions options;

    public:

        HuobiAccountService(HuobiOptions& op) {
            options = op;
            restConnection = new HuobiRestConnection(op);
        }
    public:
        const char* GET_ACCOUNTS_PATH = "/v1/account/accounts";
        const char* GET_ACCOUNT_BALANCE_PATH = "/v1/account/accounts/{account-id}/balance";
        const char* GET_SUBUSER_ACCOUNT_BALANCE_PATH = "/v1/account/accounts/{sub-uid}";
        const char* TRANSFER_SUBUSER_PATH = "/v1/subuser/transfer";
        const char* GET_SUBUSER_AGGREGATE_BALANCE_PATH = "/v1/subuser/aggregate-balance";

    public:
        const char* SUB_ACCOUNT_TOPIC = "accounts";
        const char* REQ_ACCOUNT_TOPIC = "accounts.list";
    public:
        std::vector<Account> getAccounts() override;
    };
}

#endif /* HUOBIACCOUNTSERVICE_H */

