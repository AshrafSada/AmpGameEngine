#include "AppWindow.h"

// create vector struct for specifying world space
struct vect3 {
    // representation of x,y,z (world space)
    float x, y, z;
};

// create vector struct for storing vertex position property
struct vertex {
    vect3 position;
};

AppWindow::AppWindow( ) {
}

AppWindow::~AppWindow( ) {
}

void AppWindow::onCreate( ) {
    try {
        // call the window UI base class on create
        WindowUi::onCreate( );
    }
    catch ( const std::exception& ex ) {
        LoggingBroker::logException( LoggingBroker::LOG_LEVEL_ERROR, "Failed to create the app window", ex );
        throw;
    }
}

void AppWindow::onUpdate( ) {
    try {
        // call the window ui on update
        WindowUi::onUpdate( );
    }
    catch ( const std::exception& ex ) {
        LoggingBroker::logException( LoggingBroker::LOG_LEVEL_ERROR, "Failed to update the app window", ex );
        throw;
    }
}

void AppWindow::onDestroy( ) {
    // call the window ui on destroy
    WindowUi::onDestroy( );
}
