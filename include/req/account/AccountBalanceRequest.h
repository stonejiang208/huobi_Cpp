/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AccountBalanceRequest.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月23日, 上午12:17
 */

#ifndef ACCOUNTBALANCEREQUEST_H
#define ACCOUNTBALANCEREQUEST_H

namespace Huobi {

    struct AccountBalanceRequest {

        AccountBalanceRequest(long accountId) : accountId(accountId) {
        }

        long accountId;
    };

}

#endif /* ACCOUNTBALANCEREQUEST_H */

