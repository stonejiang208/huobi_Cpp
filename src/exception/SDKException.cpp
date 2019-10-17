/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "SDKException.h"

namespace Huobi {
    std::string SDKException::RUNTIME_ERROR = "RuntimeError";
    std::string SDKException::INPUT_ERROR = "InputError";
    std::string SDKException::KEY_MISSING = "KeyMissing";
    std::string SDKException::SYS_ERROR = "SysError";
    std::string SDKException::SUBSCRIPTION_ERROR = "SubscriptionError";
    std::string SDKException::ENV_ERROR = "EnvironmentError";
    std::string SDKException::EXEC_ERROR = "ExecuteError";
}