#include "LoggingBroker.h"

LoggingBroker::LoggingBroker( ) {
}

LoggingBroker::~LoggingBroker( ) {
}

void LoggingBroker::logException( LogLevel pLogLevel, const char* message, const std::exception& excep ) {
    // get current working directory
    std::filesystem::path cwd = std::filesystem::current_path( );
    // get the file path
    std::filesystem::path filePath = cwd / "ampErrorLog.log";
    // open the file
    std::ofstream FILE( filePath, std::ios_base::app );
    // set the error message
    switch ( pLogLevel ) {
        case LoggingBroker::LOG_LEVEL_DEBUG:
            FILE << "DEBUG: " << message << excep.what( ) << std::endl;
            break;
        case LoggingBroker::LOG_LEVEL_WARNING:
            FILE << "WARNING: " << message << excep.what( ) << std::endl;
            break;
        case LoggingBroker::LOG_LEVEL_ERROR:
            FILE << "ERROR: " << message << excep.what( ) << std::endl;
            break;
        case LoggingBroker::LOG_LEVEL_FATAL:
            FILE << "FATAL: " << message << excep.what( ) << std::endl;
            break;
    }

    std::cout << "LoggingBroker::logException( ) - " << message << std::endl;
    FILE << message << "\n";
    FILE.close( );
}

void LoggingBroker::logInformation( const char* message ) {
    // get current working directory
    std::filesystem::path cwd = std::filesystem::current_path( );
    // get the file path
    std::filesystem::path filePath = cwd / "ampLog.log";
    // open the file
    std::ofstream FILE( filePath, std::ios_base::app );
    // write the message to the file
    FILE << "INFO:" << message << "\n";
    // close the file
    FILE.close( );
}
