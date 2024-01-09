#pragma once
#include <d3d11.h>
#include "SwapChain.h"

class SwapChain;
class ImDeviceContext {
public:
    ImDeviceContext( ID3D11DeviceContext* deviceContext );
    ~ImDeviceContext( );
public:
    bool ClearRenderTargetColor( SwapChain* pSwapChain, float red, float green, float blue, float alpha );
    bool Release( );

private:
    ID3D11DeviceContext* m_deviceContext;
};
