#pragma once
#include "GraphicsEngine.h"

class ImDeviceContext;
class SwapChain {
public:
    SwapChain( );
    ~SwapChain( );

    bool Init( HWND hwnd, UINT width, UINT height );
    bool Release( );

private:
    IDXGISwapChain* m_swap_chain;
    ID3D11RenderTargetView* m_rtv;

private:
    friend class ImDeviceContext;
};
