#include "LoggingBroker.h"

auto m_time_utc = std::chrono::utc_clock::now( );

LoggingBroker::LoggingBroker( ) {
    filesystem::path cwd = std::filesystem::current_path( );
    filesystem::path filePath = cwd / "AmpEngineLog.log";
    ofstream FILE( filePath, std::ios_base::app );

    ofstream ofs( filePath );
    ofs << "";
    ofs << "AMP Log File" << std::endl;
    ofs << "============" << std::endl;
    ofs.close( );
}

LoggingBroker::~LoggingBroker( ) {
}

void LoggingBroker::logException( LogLevel pLogLevel, const char* message, const exception& excep ) {
    // get current working directory
    filesystem::path cwd = std::filesystem::current_path( );
    // get the file path
    filesystem::path filePath = cwd / "AmpEngineLog.log";
    // open the file
    ofstream FILE( filePath, std::ios_base::app );

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
    filesystem::path filePath = cwd / "AmpEngineLog.log";
    // open the file
    ofstream FILE( filePath, std::ios_base::app );

    // write the message to the file
    FILE << m_time_utc << "|"
        << " INFO "
        << "|" << message << "\n";
    // close the file
    FILE.close( );
}

void LoggingBroker::logError( const char* message ) {
    // get current working directory
    filesystem::path cwd = std::filesystem::current_path( );
    // get the file path
    filesystem::path filePath = cwd / "AmpEngineLog.log";
    // open the file
    ofstream FILE( filePath, std::ios_base::app );

    // set the error message
    FILE << m_time_utc << "|"
        << " ERROR "
        << "|" << message << std::endl;
    FILE.close( );
}

void LoggingBroker::logError( HRESULT hr, const char* message ) {
    // get current working directory
    filesystem::path cwd = std::filesystem::current_path( );
    // get the file path
    filesystem::path filePath = cwd / "AmpEngineLog.log";
    // open the file
    ofstream FILE( filePath, std::ios_base::app );

    // set the error message
    FILE << m_time_utc << "|"
        << " ERROR "
        << "|" << message << "|" << hr << std::endl;
    FILE.close( );
}
