#include "GraphicsEngine.h"

GraphicsEngine::GraphicsEngine( ) {
    m_d3dDevice = 0;
    m_featureLevel = D3D_FEATURE_LEVEL_11_0;
    m_dxgi_device = 0;
    m_dxgi_adapter = 0;
    m_dxgi_factory = 0;
    m_immediateDeviceContext = 0;
    m_blobCode = nullptr;
}

GraphicsEngine::~GraphicsEngine( ) {
}

bool GraphicsEngine::createAndInit( ) {
    // Specify the driver types
    D3D_DRIVER_TYPE driverTypes[] = { D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP, D3D_DRIVER_TYPE_REFERENCE };

    // Specify the number of driver types
    UINT totalDriverTypes = ARRAYSIZE( driverTypes );

    // Specify the feature levels to be used
    D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };

    // Specify the number of feature levels
    UINT totalFeatureLevels = ARRAYSIZE( featureLevels );

    // create device and device context
    HRESULT createDeviceResult = 0;
    ID3D11DeviceContext* m_d3dDeviceContext;
    for ( UINT driverTypeIndex = 0; driverTypeIndex < totalDriverTypes;) {
        createDeviceResult = D3D11CreateDevice( 0, driverTypes[driverTypeIndex], 0, 0, featureLevels, totalFeatureLevels,
            D3D11_SDK_VERSION, &m_d3dDevice, &m_featureLevel, &m_d3dDeviceContext );
        // If the device creation was successful, break the loop
        if ( SUCCEEDED( createDeviceResult ) ) {
            break;
        }
        ++driverTypeIndex;
    }

    if ( FAILED( createDeviceResult ) ) {
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

bool GraphicsEngine::release( ) {
    // release resources in order of creation
    m_dxgi_device->Release( );
    m_dxgi_adapter->Release( );
    m_dxgi_factory->Release( );
    m_d3dDevice->Release( );
    m_immediateDeviceContext->release( );

    return true;
}

GraphicsEngine* GraphicsEngine::getSingletonGraphEng( ) {
    static GraphicsEngine instance;
    return &instance;
}

SwapChain* GraphicsEngine::createAndInitSwapChain( ) {
    SwapChain* swapChain = new SwapChain( );
    return swapChain;
}

VertexBuffer* GraphicsEngine::createVertexBuffer( ) {
    VertexBuffer* vBuffer = new VertexBuffer( );
    return vBuffer;
}

VertexShader* GraphicsEngine::createVertexShader( const void* pShaderByteCode, size_t pShaderCodeSize ) {
    VertexShader* vertexShader = new VertexShader( );

    // check vertex shader is initialized
    if ( !vertexShader->init( pShaderByteCode, pShaderCodeSize ) ) {
        vertexShader->release( );
        return nullptr;
    }

    return vertexShader;
}

bool GraphicsEngine::releaseCompiledShader( ) {
    if ( m_blobCode ) {
        m_blobCode->Release( );
    }

    return true;
}

bool GraphicsEngine::compileVertexShader( const wchar_t* pFileName, const char* pEntryPointName, const void** pShaderByteCode, size_t* pShaderCodeSize ) {
    try {
        // compile the vertex shader from HLSL file
        const char* shaderTarget = "vs_5_0"; // directX 11 vertex shader
        ID3DBlob* blobErrMsg = nullptr;
        HRESULT comFromFileHr = D3DCompileFromFile( pFileName,
            nullptr, nullptr, pEntryPointName,
            shaderTarget, 0, 0, &m_blobCode, &blobErrMsg );

        // check result
        if ( FAILED( comFromFileHr ) ) {
            if ( blobErrMsg ) {
                // releasing error buffer from memory
                blobErrMsg->Release( );
            }
            return false;
        }

        *pShaderByteCode = m_blobCode->GetBufferPointer( );
        *pShaderCodeSize = m_blobCode->GetBufferSize( );

        return true;
    }
    catch ( const std::exception& ex ) {
        LoggingBroker::logException( LoggingBroker::LOG_LEVEL_ERROR,
            "GraphicsEngine::compileVertexShader()",
            ex );
    }
}

ImDeviceContext* GraphicsEngine::getImmediateDeviceContext( ) {
    return this->m_immediateDeviceContext;
}
