#include "LoggingBroker.h"

auto m_time_utc = std::chrono::utc_clock::now( );

LoggingBroker::LoggingBroker( ) {
}

LoggingBroker::~LoggingBroker( ) {
}

void LoggingBroker::logException( LogLevel pLogLevel, const char* message, const exception& excep ) {
    // get current working directory
    filesystem::path cwd = std::filesystem::current_path( );
    // get the file path
    filesystem::path filePath = cwd / "ampErrorLog.log";
    // open the file
    ofstream FILE( filePath, std::ios_base::app );
    // clear the file
    FILE.clear( );
    FILE << "AMP Log File" << std::endl;
    FILE << "============" << std::endl;
    // set the error message
    switch ( pLogLevel ) {
        case LoggingBroker::LOG_LEVEL_DEBUG:
            FILE << m_time_utc << "|"
                << " DEBUG "
                << "|" << message << "|" << excep.what( ) << std::endl;
            break;
        case LoggingBroker::LOG_LEVEL_WARNING:
            FILE << m_time_utc << "|"
                << " WARNING "
                << "|" << message << "|" << excep.what( ) << std::endl;
            break;
        case LoggingBroker::LOG_LEVEL_ERROR:
            FILE << m_time_utc << "|"
                << " ERROR "
                << "|" << message << "|" << excep.what( ) << std::endl;
            break;
        case LoggingBroker::LOG_LEVEL_FATAL:
            FILE << m_time_utc << "|"
                << " FATAL "
                << "|" << message << "|" << excep.what( ) << std::endl;
            break;
    }
    FILE.close( );
}

void LoggingBroker::logInformation( const char* message ) {
    // get current working directory
    filesystem::path cwd = std::filesystem::current_path( );
    // get the file path
    filesystem::path filePath = cwd / "ampLog.log";
    // open the file
    ofstream FILE( filePath, std::ios_base::app );
    // clear the log file
    FILE.clear( );
    // write the message to the file
    FILE << m_time_utc << "|"
        << " INFO "
        << "|" << message << "\n";
    // close the file
    FILE.close( );
}
