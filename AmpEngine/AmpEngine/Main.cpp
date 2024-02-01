#include <iostream>
#include "AppWindow.h"
#include "LoggingBroker.h"

int main( ) {
    try {
        // notifiying the user that application is running
        std::cout << "Application is running..." << std::endl;

        LoggingBroker::logInformation( "Amp Engine Running..." );

        AppWindow app;
        // HACK: check for app.init( ) and run while loop only if true
        // multiple window creation, that waht is running means
        if ( app.init( ) == true ) {
            while ( app.isRunning( ) ) {
                app.broadcast( );
            }
        }
    }
    catch ( const std::exception& ex ) {
        LoggingBroker::logException( LoggingBroker::LOG_LEVEL_ERROR, "Failed to run the app", ex );
        throw;
    }
    return 0;
}
