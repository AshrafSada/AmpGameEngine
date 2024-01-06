#include "AppWindow.h"

AppWindow::AppWindow( ) {
}

AppWindow::~AppWindow( ) {
}

void AppWindow::onCreate( ) {
    WindowUi::onCreate( );
    GraphicsEngine::GetInstance( )->Init( );
}

void AppWindow::onUpdate( ) {
    WindowUi::onUpdate( );
}

void AppWindow::onDestroy( ) {
    WindowUi::onDestroy( );
    // Release the graphics engine
    GraphicsEngine::GetInstance( )->Release( );
}
