#include "ImDeviceContext.h"

ImDeviceContext::ImDeviceContext( ID3D11DeviceContext* deviceContext ) : m_device_context( deviceContext ) {
}

ImDeviceContext::~ImDeviceContext( ) {
}

bool ImDeviceContext::clearRenderTargetColor( SwapChain* pSwapChain, float red, float green, float blue, float alpha ) {
    FLOAT clear_color[] = { red, green, blue, alpha };
    m_device_context->ClearRenderTargetView( pSwapChain->m_rtv, clear_color );
    m_device_context->OMSetRenderTargets( 1, &pSwapChain->m_rtv, NULL ); // set render target view to output merger stage
    return true;
}

bool ImDeviceContext::release( ) {
    m_device_context->Release( );
    delete this;
    return true;
}

void ImDeviceContext::drawTriangleSet( UINT pVertexCount, UINT pVertexStartIndex ) {
    // draw triangle
    m_device_context->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
    m_device_context->Draw( pVertexCount, pVertexStartIndex );
}

void ImDeviceContext::setViewPortSize( float pWidth, float pHeight ) {
    // create a viewport
    D3D11_VIEWPORT viewport = { };
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = pWidth;
    viewport.Height = pHeight;
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;

    // set the viewport
    m_device_context->RSSetViewports( 1, &viewport );
}
