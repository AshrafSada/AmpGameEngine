#pragma once
#include "GraphicsEngine.h"
#include <d3d11.h>
#include <exception>
#include "LoggingBroker.h"

class ImDeviceContext;

class SwapChain {
public:
    // constructor and destructor
    SwapChain( );
    ~SwapChain( );

public:
    // methods
    bool init( HWND hwnd, UINT width, UINT height );
    bool present( bool vsync );
    bool release( );

private:
    IDXGISwapChain* m_swap_chain;
    ID3D11RenderTargetView* m_render_target_view;

private:
    friend class ImDeviceContext;
};
