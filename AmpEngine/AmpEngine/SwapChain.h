#pragma once
#include "GraphicsEngine.h"

class SwapChain {
public:
    SwapChain( );
    ~SwapChain( );

    bool Init( HWND hwnd, UINT width, UINT height );
    bool Release( );

private:
    IDXGISwapChain* m_swap_chain;
};
