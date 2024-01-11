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

    bool init( HWND hwnd, UINT width, UINT height );
    bool present( bool vsync );
    bool release( );

private:
    IDXGISwapChain* m_swap_chain;
    ID3D11RenderTargetView* m_rtv;

private:
    friend class ImDeviceContext;
};
