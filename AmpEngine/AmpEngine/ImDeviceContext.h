#pragma once
#include "SwapChain.h"
#include "VertexShader.h"

class SwapChain;
class VertexBuffer;
class VertexShader;

class ImDeviceContext {
public:
    // constructor and destructor
    ImDeviceContext( ID3D11DeviceContext* deviceContext );
    ~ImDeviceContext( );

public:
    // methods
    bool clearRenderTargetColor( SwapChain* pSwapChain, float red, float green, float blue, float alpha );
    void drawTriangleList( UINT pVertexCount, UINT pStartVertexIndex );
    void drawTriangleStrip( UINT pVertexCount, UINT pStartVertexIndex );
    bool release( );

public:
    // setters
    void setVertexBuffer( VertexBuffer* pVertextBuffer );
    void setViewPortSize( float pWidth, float pHeight );
    void setVertexShader( VertexShader* pVertexShader );

public:
    // vertex methods
    void DrawTriangleList( UINT pVertexCount, UINT pVertextStartIndex );

private:
    // private fields
    ID3D11DeviceContext* m_device_context;
};
