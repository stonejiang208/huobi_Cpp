/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SubAccountChangeRequest.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月23日, 上午12:30
 */

#ifndef SUBACCOUNTCHANGEREQUEST_H
#define SUBACCOUNTCHANGEREQUEST_H

namespace Huobi {

    struct SubAccountChangeRequest {

        SubAccountChangeRequest(BalanceMode balanceMode) : balanceMode(balanceMode) {
        }

        SubAccountChangeRequest() {
        }
        BalanceMode balanceMode;
    };

}

#endif /* SUBACCOUNTCHANGEREQUEST_H */

