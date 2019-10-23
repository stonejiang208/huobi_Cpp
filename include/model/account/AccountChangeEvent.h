/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AccountChangeEvent.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月23日, 上午12:32
 */

#ifndef ACCOUNTCHANGEEVENT_H
#define ACCOUNTCHANGEEVENT_H
#include "AccountChange.h"
namespace Huobi {

    struct AccountChangeEvent {
        std::string event;
        std::vector<AccountChange> list;
    };

}

#endif /* ACCOUNTCHANGEEVENT_H */

