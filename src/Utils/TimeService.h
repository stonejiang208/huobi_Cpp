/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TimeService.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月18日, 上午9:55
 */

#ifndef TIMESERVICE_H
#define TIMESERVICE_H


#include <chrono>
#include <iostream>

namespace Huobi {

    class TimeService {
    public:

        static long getCurrentTimeStamp() {
            std::chrono::milliseconds ms = std::chrono::duration_cast< std::chrono::milliseconds >(
                    std::chrono::system_clock::now().time_since_epoch()
                    );
            return ms.count();
        }
    };
}



#endif /* TIMESERVICE_H */

