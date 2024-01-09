#pragma once
#include "GraphicsEngine.h"
#include <d3d11.h>
#include <exception>
#include "LoggingBroker.h"

class ImDeviceContext;
class SwapChain {
public:
    SwapChain( );
    ~SwapChain( );

    bool Init( HWND hwnd, UINT width, UINT height );
    bool Present( bool vsync );
    bool Release( );

private:
    IDXGISwapChain* m_swap_chain;
    ID3D11RenderTargetView* m_rtv;

private:
    friend class ImDeviceContext;
};
