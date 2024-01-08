#include <iostream>
#include "AppWindow.h"

int main( ) {
    std::cout << "Amp Engine Running..." << std::endl;

    AppWindow app;
    // HACK: check for app.init( ) and run while loop only if true
    // multiple window creation, that waht is running means
    if ( app.init( ) == true ) {
        while ( app.isRunning( ) ) {
            app.broadcast( );
        }
    }
    return 0;
}
