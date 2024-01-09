#pragma once
#include <d3d11.h>
#include "SwapChain.h"
#include "ImDeviceContext.h"

class SwapChain;
class ImDeviceContext;
class GraphicsEngine {
public:
    GraphicsEngine( );
    ~GraphicsEngine( );

    bool CreateAndInit( );
    bool Release( );

public:
    SwapChain* CreateSwapChain( );
    ImDeviceContext* GetImmediateDeviceContext( );

public:
    // singleton instance getter
    static GraphicsEngine* GetSingleton( );
private:
    ID3D11Device* m_d3dDevice;
    D3D_FEATURE_LEVEL m_featureLevel;
    IDXGIDevice* m_dxgi_device;
    IDXGIAdapter* m_dxgi_adapter;
    IDXGIFactory* m_dxgi_factory;

private:
    ImDeviceContext* m_immediateDeviceContext;
private:
    friend class SwapChain;
};
