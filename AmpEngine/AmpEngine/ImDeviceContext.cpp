#include "ImDeviceContext.h"

ImDeviceContext::ImDeviceContext( ID3D11DeviceContext* deviceContext ) : m_device_context( deviceContext ) {
}

ImDeviceContext::~ImDeviceContext( ) {
}

void ImDeviceContext::clearRenderTargetColor( SwapChain* pSwapChain, float red, float green, float blue, float alpha ) {
    // clear color RGBA
    FLOAT clear_color[] = { red, green, blue, alpha };

    // call clear render target view from DX11
    m_device_context->ClearRenderTargetView( pSwapChain->m_render_target_view, clear_color );

    // set OM Set Render Targets to output merger stage
    m_device_context->OMSetRenderTargets( 1, &pSwapChain->m_render_target_view, NULL );
}

void ImDeviceContext::drawTriangleList( UINT pVertexCount, UINT pStartVertexIndex ) {
    // triangle list
    m_device_context->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
    m_device_context->Draw( pVertexCount, pStartVertexIndex );
}

void ImDeviceContext::drawTriangleStrip( UINT pVertexCount, UINT pStartVertexIndex ) {
    // call IA Set primitive topology to set primitive topology to input assembler stage IA
    m_device_context->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );
    // call the draw method from DX11 to draw triangle list from input assembler stage IA
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
    UINT vbOffset = 0; // offset

    // call IASet vertex buffers from DX11 to set vertex buffer to input assembler stage IA
    m_device_context->IASetVertexBuffers( 0, 1, &pVertextBuffer->m_buffer_pointer, &vbStrides, &vbOffset );

    // call IASet input layout from DX11 to set input layout to input assembler stage IA
    m_device_context->IASetInputLayout( pVertextBuffer->m_input_layout );
}

void ImDeviceContext::setViewPortSize( float pWidth, float pHeight ) {
    // create view port from DX11, and set the view port size
    D3D11_VIEWPORT viewPort = { };
    viewPort.MinDepth = 0.0f;
    viewPort.MaxDepth = 1.0f;
    viewPort.Width = pWidth;
    viewPort.Height = pHeight;

    // call RSSetViewports from DX11 to set view port to rasterizer stage RS
    m_device_context->RSSetViewports( 1, &viewPort );
}

void ImDeviceContext::setVertexShader( VertexShader* pVertexShader ) {
    // set vertex shader to vertex shader stage VS
    m_device_context->VSSetShader( pVertexShader->m_vertex_shader, nullptr, 0 );
}
