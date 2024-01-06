#include "GraphicsEngine.h"

GraphicsEngine::GraphicsEngine( ) {
}

GraphicsEngine::~GraphicsEngine( ) {
}

bool GraphicsEngine::Init( ) {
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

    // Create a device and device context

    return true;
}

bool GraphicsEngine::Release( ) {
    // release device and device context
    m_d3dDevice->Release( );
    m_d3dDeviceContext->Release( );
    return true;
}

GraphicsEngine* GraphicsEngine::GetInstance( ) {
    static GraphicsEngine instance;
    return &instance;
}
