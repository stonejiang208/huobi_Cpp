/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ConnectionFactory.h"
namespace Huobi {

    struct lws_context* ConnectionFactory::context = nullptr;
    struct lws_protocols ConnectionFactory:: protocols[] = {
        {
            "example-protocol",
            event_cb,
            0,
            4096 * 100
        },
        { NULL, NULL, 0, 0}
    };

}