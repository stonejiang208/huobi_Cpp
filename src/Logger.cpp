#include <stdbool.h>

#include "Huobi/Logger.h"

namespace Huobi {

    class LoggerImpl {
    public:

        static LoggerImpl* instance() {
            static LoggerImpl obj; // Assumes T has a protected default constructor.
            return &obj;
        }

        Logger::LogLevel log_level_ = Logger::WARNING;
        std::string log_file_locate_ = "./huobi.log";
        FILE* log_fp_ = nullptr;
        bool enable_to_stdout_ = false;

        void WriteLog(Logger::LogLevel level, const char* level_str, const char *msg, va_list arg) {
            if (log_level_ >= level) {
                return;
            }
            time_t t = time(NULL);
            struct tm *local = gmtime(&t);
            char buf[1024];
            sprintf(buf, "%04d-%02d-%02dT%02d:%02d:%02d %s :%s\n", local->tm_year + 1900,
                    local->tm_mon + 1,
                    local->tm_mday,
                    local->tm_hour,
                    local->tm_min,
                    local->tm_sec, level_str, msg);
            if (log_fp_ == nullptr) {
                log_fp_ = fopen(log_file_locate_.c_str(), "a");
            }
            if (log_fp_ != nullptr) {
                vfprintf(log_fp_, buf, arg);
                fflush(log_fp_);
            }
            if (enable_to_stdout_) {
                vfprintf(stdout, buf, arg);
                fflush(stdout);
            }
        }
    };

    void Logger::LogInfo(const char* msg, ...) {
        va_list va_list_ptr;
        va_start(va_list_ptr, msg);
        LoggerImpl::instance()->WriteLog(Logger::INFO, "[INFO] ", msg, va_list_ptr);
        va_end(va_list_ptr);
    }

    void Logger::LogDebug(const char* msg, ...) {
        va_list va_list_ptr;
        va_start(va_list_ptr, msg);
        LoggerImpl::instance()->WriteLog(Logger::DEBUG, "[DEBUG] ", msg, va_list_ptr);
        va_end(va_list_ptr);
    }

    void Logger::LogWarning(const char* msg, ...) {
        va_list va_list_ptr;
        va_start(va_list_ptr, msg);
        LoggerImpl::instance()->WriteLog(Logger::WARNING, "[WARNING] ", msg, va_list_ptr);
        va_end(va_list_ptr);
    }

    void Logger::LogCritical(const char* msg, ...) {
        va_list va_list_ptr;
        va_start(va_list_ptr, msg);
        LoggerImpl::instance()->WriteLog(Logger::CRITICAL, "[CRITICAL] ", msg, va_list_ptr);
        va_end(va_list_ptr);
    }

    void Logger::SetLogLevel(LogLevel level) {
        LoggerImpl::instance()->log_level_ = level;
    }

    void Logger::setLogfilelocate(std::string &util_file) {
        LoggerImpl::instance()->log_file_locate_ = util_file;
    }

    void Logger::EnableShowLogToSTDOUT(bool enabled) {
        LoggerImpl::instance()->enable_to_stdout_ = enabled;
    }
}