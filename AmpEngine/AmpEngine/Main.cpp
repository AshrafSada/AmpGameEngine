#include <iostream>
#include "AppWindow.h"

int main( ) {
    std::cout << "Amp Engine Running..." << std::endl;

    AppWindow app;
    // HACK: on app.init( ) only we set the while to is running to prevent
    // multiple window creation, that waht is running means
    if ( app.init( ) == true ) {
        while ( app.isRunning( ) ) {
            app.broadcast( );
        }
    }
    return 0;
}
