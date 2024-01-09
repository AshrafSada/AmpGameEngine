#include "AppWindow.h"

AppWindow::AppWindow( ) {
    m_swap_chain = nullptr;
}

AppWindow::~AppWindow( ) {
}

void AppWindow::onCreate( ) {
    try {
        WindowUi::onCreate( );
        // Create the graphics engine and initialize it
        GraphicsEngine::GetSingleton( )->CreateAndInit( );
        // Create the swap chain from the factory method in the graphics engine
        m_swap_chain = GraphicsEngine::GetSingleton( )->CreateSwapChain( );
        // get client window size
        RECT rect = this->getClientWindowRect( );
        // init the swap chain with the window handle and window client size
        m_swap_chain->Init( this->m_hwnd, rect.left - rect.right, rect.top - rect.bottom );
    }
    catch ( const std::exception& ex ) {
        LoggingBroker::logException( LoggingBroker::LOG_LEVEL_ERROR, "Failed to create the app window", ex );
        throw;
    }
}

void AppWindow::onUpdate( ) {
    try {
        // Clear the render target
        GraphicsEngine::GetSingleton( )->GetImmediateDeviceContext( )->ClearRenderTargetColor( this->m_swap_chain, 0, 0, 1, 1 );
        // Present the back buffer to the screen
        this->m_swap_chain->Present( false );
        WindowUi::onUpdate( );
    }
    catch ( const std::exception& ex ) {
        LoggingBroker::logException( LoggingBroker::LOG_LEVEL_ERROR, "Failed to update the app window", ex );
        throw;
    }
}

void AppWindow::onDestroy( ) {
    WindowUi::onDestroy( );
    // Release the swap chain
    m_swap_chain->Release( );
    // Release the graphics engine
    GraphicsEngine::GetSingleton( )->Release( );
}
