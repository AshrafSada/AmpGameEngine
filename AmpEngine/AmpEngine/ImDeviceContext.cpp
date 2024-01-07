#include "ImDeviceContext.h"

ImDeviceContext::ImDeviceContext( ID3D11DeviceContext* deviceContext ) :m_deviceContext( deviceContext ) {
}

ImDeviceContext::~ImDeviceContext( ) {
}

bool ImDeviceContext::ClearRenderTargetColor( SwapChain* pSwapChain, float red, float green, float blue, float alpha ) {
    FLOAT clear_color[4] = { red, green, blue, alpha };
    m_deviceContext->ClearRenderTargetView( pSwapChain->m_rtv, clear_color );
    return true;
}

bool ImDeviceContext::Release( ) {
    m_deviceContext->Release( );
    delete this;
    return true;
}
