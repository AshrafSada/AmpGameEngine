#pragma once
#include <d3d11.h>
#include "ImDeviceContext.h"
#include "SwapChain.h"
#include "VertexBuffer.h"

class ImDeviceContext;
class SwapChain;
class VertexBuffer;

class GraphicsEngine {
public:
    // constructor and destructor
    GraphicsEngine( );
    ~GraphicsEngine( );

public:
    // methods
    bool createAndInit( );
    bool release( );

public:
    // getters and setters
    ImDeviceContext* getImmediateDeviceContext( );
    SwapChain* createAndInitSwapChain( );
    VertexBuffer* createVertexBuffer( );

public:
    // singleton instance getter
    static GraphicsEngine* getSingletonGraphEng( );

private:
    ID3D11Device* m_d3dDevice;
    D3D_FEATURE_LEVEL m_featureLevel;
    IDXGIDevice* m_dxgi_device;
    IDXGIAdapter* m_dxgi_adapter;
    IDXGIFactory* m_dxgi_factory;
    ImDeviceContext* m_immediateDeviceContext;

private:
    // sub-classes friendship
    friend class SwapChain;
    friend class VertexBuffer;
};
