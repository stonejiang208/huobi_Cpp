/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AccountClient.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月22日, 下午6:35
 */

#ifndef ACCOUNTCLIENT_H
#define ACCOUNTCLIENT_H
#include <vector>
#include "model/account/Account.h"
namespace Huobi
{

    struct AccountClient {
        
        virtual std::vector<Account> getAccounts() = 0;

//        virtual AccountBalance getAccountBalance(const AccountBalanceRequest& request) = 0;
//
//        virtual long transferSubuser(const TransferSubuserRequest& request) = 0;
//
//        virtual std::vector<AccountBalance> getSubuserAccountBalance(long subuserId) = 0;
//
//        virtual std::vector<SubuserAggregateBalance> getSubuserAggregateBalance() = 0;
//
//        virtual void subAccounts(const SubAccountChangeRequest& request, ResponseCallback<AccountChangeEvent> callback) = 0;
//
//        virtual void reqAccounts(ResponseCallback<AccountReq> callback) = 0;

    };

}

#endif /* ACCOUNTCLIENT_H */

