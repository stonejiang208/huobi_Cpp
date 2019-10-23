/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AccountChangeEventParser.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月23日, 下午7:03
 */

#ifndef ACCOUNTCHANGEEVENTPARSER_H
#define ACCOUNTCHANGEEVENTPARSER_H
#include "model/account/AccountChangeEvent.h"
#include "AccountChangeParser.h"
namespace Huobi {

    class AccountChangeEventParser {
    public:

        static AccountChangeEvent parse(JsonWrapper& json) {

            AccountChangeEvent event;
            event.event=json.getString("event");          
            JsonWrapper list=json.getJsonObjectOrArray("list");
            event.list = AccountChangeParser::parseArray(list);
            return event;
        }
    };

}


#endif /* ACCOUNTCHANGEEVENTPARSER_H */

