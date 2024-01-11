#pragma once
#include "SwapChain.h"
#include <d3d11.h>

class SwapChain;
class VertexBuffer;

class ImDeviceContext {
public:
    // constructor and destructor
    ImDeviceContext( ID3D11DeviceContext* deviceContext );
    ~ImDeviceContext( );

public:
    // methods
    bool clearRenderTargetColor( SwapChain* pSwapChain, float red, float green, float blue, float alpha );
    bool release( );

public:
    // setters
    void setVertexBuffer( VertexBuffer* pVertextBuffer );
    void setViewPortSize( float pWidth, float pHeight );

public:
    // vertex methods
    void DrawTriangleList( UINT pVertexCount, UINT pVertextStartIndex );
private:
    // private fields
    ID3D11DeviceContext* m_device_context;
};
