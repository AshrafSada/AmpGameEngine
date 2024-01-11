#pragma once
#include "SwapChain.h"
#include <d3d11.h>

class SwapChain;
class ImDeviceContext {
public:
    // constructor and destructor
    ImDeviceContext( ID3D11DeviceContext* deviceContext );
    ~ImDeviceContext( );

public:
    // methods
    bool clearRenderTargetColor( SwapChain* pSwapChain, float red, float green, float blue, float alpha );
    bool release( );

    void drawTriangleSet( UINT pVertexCount, UINT pVertexStartIndex );
    void setViewPortSize( float pWidth, float pHeight );

private:
    // private fields
    ID3D11DeviceContext* m_device_context;
};
