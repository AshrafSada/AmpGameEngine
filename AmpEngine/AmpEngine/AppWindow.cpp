#include "AppWindow.h"

AppWindow::AppWindow() { m_swap_chain = nullptr; }

AppWindow::~AppWindow() {}

void AppWindow::onCreate() {
    try {
        WindowUi::onCreate();
        // Create the graphics engine and initialize it
        GraphicsEngine::getSingletonGraphEng()->createAndInit();
        // Create the swap chain from the factory method in the graphics engine
        m_swap_chain = GraphicsEngine::getSingletonGraphEng()->createAndInitSwapChain();
        // get client window size
        RECT rect = this->getClientWindowRect();
        // init the swap chain with the size of the client window
        //! important: deduct (right - left) and (bottom - top) otherwise the window will be too big and swap chain
        //! will be null
        m_swap_chain->init(this->m_hwnd, rect.right - rect.left, rect.bottom - rect.top);
    } catch (const std::exception& ex) {
        LoggingBroker::logException(LoggingBroker::LOG_LEVEL_ERROR, "Failed to create the app window", ex);
        throw;
    }
}

void AppWindow::onUpdate() {
    try {
        // Clear the render target
        GraphicsEngine::getSingletonGraphEng()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
                                                                                                    0, 1, 0, 1);
        // Present the back buffer to the screen
        this->m_swap_chain->present(false);
        WindowUi::onUpdate();
    } catch (const std::exception& ex) {
        LoggingBroker::logException(LoggingBroker::LOG_LEVEL_ERROR, "Failed to update the app window", ex);
        throw;
    }
}

void AppWindow::onDestroy() {
    WindowUi::onDestroy();
    // Release the swap chain
    m_swap_chain->release();
    // Release the graphics engine
    GraphicsEngine::getSingletonGraphEng()->release();
}
