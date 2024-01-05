#include "GraphicsEngine.h"
#include <d3d11.h>

GraphicsEngine::GraphicsEngine( ) { }

GraphicsEngine::~GraphicsEngine( ) { }

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

    // Create a device and device context

    return true;
}

bool GraphicsEngine::Release( ) {
    return true;
}
