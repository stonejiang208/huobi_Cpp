/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TransferSubuserRequest.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月23日, 上午12:21
 */

#ifndef TRANSFERSUBUSERREQUEST_H
#define TRANSFERSUBUSERREQUEST_H

#include "constant/enums.h"
#include "constant/Decimal.h"


namespace Huobi {

    struct TransferSubuserRequest {

        TransferSubuserRequest(long subUid,
                std::string currency,
                Decimal amount,
                TransferMasterType type) : subUid(subUid), currency(currency), amount(amount), type(type) {
        }

        long subUid;
        std::string currency;
        Decimal amount;
        TransferMasterType type;
    };

}

#endif /* TRANSFERSUBUSERREQUEST_H */

