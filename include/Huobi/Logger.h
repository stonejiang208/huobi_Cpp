#ifndef LOGGER_H
#define LOGGER_H

#include <time.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include "Enums.h"

namespace Huobi {

    class Logger {
    public:

        enum LogLevel {
            DEBUG = 1,
            INFO = 2,
            WARNING = 3,
            CRITICAL = 4
        };

        static void LogDebug(const char* msg, ...);
        static void LogWarning(const char* msg, ...);
        static void LogCritical(const char* msg, ...);
        static void LogInfo(const char* msg, ...);

        static void EnableShowLogToSTDOUT(bool enabled);
        static void SetLogLevel(LogLevel level);
        static void setLogfilelocate(std::string &pDebug_log_file);

    };
}
#endif /* LOGGER_H */

