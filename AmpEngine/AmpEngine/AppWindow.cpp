#include "AppWindow.h"

AppWindow::AppWindow( ) {
    m_swap_chain = nullptr;
}

AppWindow::~AppWindow( ) {
}

void AppWindow::onCreate( ) {
    WindowUi::onCreate( );
    GraphicsEngine::GetInstance( )->Init( );
    // Create the swap chain from the factory method in the graphics engine
    m_swap_chain = GraphicsEngine::GetInstance( )->CreateSwapChain( );
    // get client window size
    RECT rect = this->getClientWindowRect( );
    // init the swap chain with the window handle and window client size
    m_swap_chain->Init( this->m_hwnd, rect.left - rect.right, rect.top - rect.bottom );
}

void AppWindow::onUpdate( ) {
    WindowUi::onUpdate( );
}

void AppWindow::onDestroy( ) {
    WindowUi::onDestroy( );
    // Release the swap chain
    m_swap_chain->Release( );
    // Release the graphics engine
    GraphicsEngine::GetInstance( )->Release( );
}
