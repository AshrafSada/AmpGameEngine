#pragma once
#include "WindowUi.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"

class AppWindow : public WindowUi {
public:
    AppWindow( );
    ~AppWindow( );

    // Inherited via WindowUi
    void onCreate( ) override;
    void onUpdate( ) override;
    void onDestroy( ) override;

private:
    SwapChain* m_swap_chain;
};
