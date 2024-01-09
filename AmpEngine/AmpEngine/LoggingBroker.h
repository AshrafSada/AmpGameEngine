#pragma once
#include <fstream>
#include <iostream>
#include <filesystem>

class LoggingBroker {
public:
    LoggingBroker( );
    ~LoggingBroker( );

    enum LogLevel {
        LOG_LEVEL_DEBUG,
        LOG_LEVEL_INFO,
        LOG_LEVEL_WARNING,
        LOG_LEVEL_ERROR,
        LOG_LEVEL_FATAL
    };

public:
    static void logException( LogLevel pLogLevel, const char* message, const std::exception& excep );
    static void logInformation( const char* message );
};
