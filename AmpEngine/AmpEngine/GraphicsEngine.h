#pragma once
#include <d3d11.h>
#include "SwapChain.h"

class SwapChain;
class GraphicsEngine {
public:
    GraphicsEngine( );
    ~GraphicsEngine( );

    bool Init( );
    bool Release( );

    // singleton instance getter
    static GraphicsEngine* GetInstance( );

    // instance of swap chain
    SwapChain* CreateSwapChain( );

private:
    ID3D11Device* m_d3dDevice;
    ID3D11DeviceContext* m_d3dDeviceContext;
    D3D_FEATURE_LEVEL m_featureLevel;
    IDXGIDevice* m_dxgi_device;
    IDXGIAdapter* m_dxgi_adapter;
    IDXGIFactory* m_dxgi_factory;

private:
    friend class SwapChain;
};
