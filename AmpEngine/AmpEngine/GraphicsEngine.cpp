#include "GraphicsEngine.h"

GraphicsEngine::GraphicsEngine( ) {
    m_d3dDevice = 0;
    m_featureLevel = D3D_FEATURE_LEVEL_11_0;
    m_dxgi_device = 0;
    m_dxgi_adapter = 0;
    m_dxgi_factory = 0;
    m_immediateDeviceContext = 0;
}

GraphicsEngine::~GraphicsEngine( ) {
}

bool GraphicsEngine::CreateAndInit( ) {
    // Specify the driver types
    D3D_DRIVER_TYPE driverTypes[] = {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE
    };

    // Specify the number of driver types
    UINT totalDriverTypes = ARRAYSIZE( driverTypes );

    // Specify the feature levels to be used
    D3D_FEATURE_LEVEL featureLevels[] = {
        D3D_FEATURE_LEVEL_11_0
    };

    // Specify the number of feature levels
    UINT totalFeatureLevels = ARRAYSIZE( featureLevels );

    // create device and device context
    HRESULT result = 0;
    ID3D11DeviceContext* m_d3dDeviceContext;
    for ( UINT driverTypeIndex = 0; driverTypeIndex < totalDriverTypes; ) {
        result = D3D11CreateDevice( 0, driverTypes[driverTypeIndex], 0, 0,
            featureLevels, totalFeatureLevels, D3D11_SDK_VERSION,
            &m_d3dDevice, &m_featureLevel, &m_d3dDeviceContext );
        // If the device creation was successful, break the loop
        if ( SUCCEEDED( result ) ) {
            break;
        }
        ++driverTypeIndex;
    }

    if ( FAILED( result ) ) {
        return false;
    }

    m_immediateDeviceContext = new ImDeviceContext( m_d3dDeviceContext );

    // Query graphics interface GI device
    m_d3dDevice->QueryInterface( __uuidof( IDXGIDevice ), ( void** )&m_dxgi_device );
    // query GI adapter
    m_dxgi_device->GetParent( __uuidof( IDXGIAdapter ), ( void** )&m_dxgi_adapter );
    // query GI factory
    m_dxgi_adapter->GetParent( __uuidof( IDXGIFactory ), ( void** )&m_dxgi_factory );

    return true;
}

bool GraphicsEngine::Release( ) {
    // release resources in order of creation
    m_dxgi_device->Release( );
    m_dxgi_adapter->Release( );
    m_dxgi_factory->Release( );
    m_d3dDevice->Release( );
    m_immediateDeviceContext->Release( );
    return true;
}

GraphicsEngine* GraphicsEngine::GetSingleton( ) {
    static GraphicsEngine instance;
    return &instance;
}

SwapChain* GraphicsEngine::CreateSwapChain( ) {
    SwapChain* swapChain = new SwapChain( );
    return swapChain;
}

ImDeviceContext* GraphicsEngine::GetImmediateDeviceContext( ) {
    return this->m_immediateDeviceContext;
}
