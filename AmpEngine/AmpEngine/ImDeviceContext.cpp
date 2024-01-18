#include "ImDeviceContext.h"

ImDeviceContext::ImDeviceContext( ID3D11DeviceContext* deviceContext ) : m_device_context( deviceContext ) {
}

ImDeviceContext::~ImDeviceContext( ) {
}

bool ImDeviceContext::clearRenderTargetColor( SwapChain* pSwapChain, float red, float green, float blue, float alpha ) {
    FLOAT clear_color[] = { red, green, blue, alpha };
    m_device_context->ClearRenderTargetView( pSwapChain->m_rtv, clear_color );
    m_device_context->OMSetRenderTargets( 1, &pSwapChain->m_rtv, NULL ); // set render target view to output merger stage

    // set OM Set Render Targets
    m_device_context->OMSetRenderTargets( 1, &pSwapChain->m_rtv, NULL );

    return true;
}

void ImDeviceContext::drawTriangleList( UINT pVertexCount, UINT pStartVertexIndex ) {
    // triangle list
    m_device_context->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
    m_device_context->Draw( pVertexCount, pStartVertexIndex );
}

void ImDeviceContext::drawTriangleStrip( UINT pVertexCount, UINT pStartVertexIndex ) {
    // trinagle strip
    m_device_context->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );
    m_device_context->Draw( pVertexCount, pStartVertexIndex );
}

bool ImDeviceContext::release( ) {
    m_device_context->Release( );
    delete this;
    return true;
}

void ImDeviceContext::setVertexBuffer( VertexBuffer* pVertextBuffer ) {
    // call IASet buffers from DX11 for vertex buffer
    UINT vbStrides = pVertextBuffer->m_vertext_size; // buffer size
    UINT vbOffset = 0;
    m_device_context->IASetVertexBuffers( 0, 1, &pVertextBuffer->m_buffer_pointer, &vbStrides, &vbOffset );
    // call IASet input layout from DX11 for input layout
    m_device_context->IASetInputLayout( pVertextBuffer->m_input_layout );
}

void ImDeviceContext::setViewPortSize( float pWidth, float pHeight ) {
    // specify view port from DX11
    D3D11_VIEWPORT viewPort = { };
    viewPort.MinDepth = 0.0f;
    viewPort.MaxDepth = 1.0f;
    viewPort.Width = pWidth;
    viewPort.Height = pHeight;

    // call RS Set viewport
    m_device_context->RSSetViewports( 1, &viewPort );
}

void ImDeviceContext::setVertexShader( VertexShader* pVertexShader ) {
    m_device_context->VSSetShader( pVertexShader->m_vertex_shader, nullptr, 0 );
}

void ImDeviceContext::DrawTriangleList( UINT pVertexCount, UINT pVertextStartIndex ) {
    // call IA Set primitive topology
    m_device_context->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
    // call the draw method from DX11
    m_device_context->Draw( pVertexCount, pVertextStartIndex );
}
