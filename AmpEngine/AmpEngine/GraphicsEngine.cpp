#include "GraphicsEngine.h"

GraphicsEngine::GraphicsEngine( ) {
    m_d3dDevice = 0;
    m_featureLevel = D3D_FEATURE_LEVEL_11_0;
    m_dxgi_device = 0;
    m_dxgi_adapter = 0;
    m_dxgi_factory = 0;
    m_immediateDeviceContext = 0;
    m_blobCode = nullptr;
    m_vertex_shader_blob = nullptr;
    m_pixel_shader_blob = nullptr;
    m_vertex_shader = nullptr;
    m_pixel_shader = nullptr;
    m_d3dDeviceContext = 0;
}

GraphicsEngine::~GraphicsEngine( ) {
}

bool GraphicsEngine::init( ) {
    try {
        // create driver types
        D3D_DRIVER_TYPE driverTypes[] = {
            D3D_DRIVER_TYPE_HARDWARE,
            D3D_DRIVER_TYPE_WARP,
            D3D_DRIVER_TYPE_REFERENCE
        };

        // get number of driver types
        UINT totalDriverTypes = ARRAYSIZE( driverTypes );

        // create feature levels
        D3D_FEATURE_LEVEL featureLevels[] = {
            D3D_FEATURE_LEVEL_11_0
        };

        // get number of feature levels
        UINT totalFeatureLevels = ARRAYSIZE( featureLevels );

        // set HRESULT to 0
        HRESULT hrCreateDevice = 0;

        // create device and device context
        for ( UINT driverTypeIndex = 0; driverTypeIndex < totalDriverTypes; ) {
            hrCreateDevice = D3D11CreateDevice( NULL, driverTypes[driverTypeIndex], nullptr, 0,
                                                featureLevels, totalFeatureLevels, D3D11_SDK_VERSION,
                                                &m_d3dDevice, &m_featureLevel, &m_d3dDeviceContext );

            if ( SUCCEEDED( hrCreateDevice ) ) {
                break;
            }
            ++driverTypeIndex;
        }

        // check if device and device context were created
        if ( FAILED( hrCreateDevice ) ) {
            return false;
        }

        // assign device context
        m_immediateDeviceContext = new ImDeviceContext( m_d3dDeviceContext );

        // get DXGI device
        m_d3dDevice->QueryInterface( __uuidof( IDXGIDevice ), ( void** )&m_dxgi_device );

        // get DXGI adapter
        m_dxgi_device->GetParent( __uuidof( IDXGIAdapter ), ( void** )&m_dxgi_adapter );

        // get DXGI factory
        m_dxgi_adapter->GetParent( __uuidof( IDXGIFactory ), ( void** )&m_dxgi_factory );

        return true;
    }
    catch ( const std::exception& ex ) {
        LoggingBroker::logException( LoggingBroker::LOG_LEVEL_ERROR,
                                                "GraphicsEngine::createAndInit()",
                                                ex );
    }
}

bool GraphicsEngine::release( ) {
    // release resources in order of creation
    m_dxgi_device->Release( );
    m_dxgi_adapter->Release( );
    m_dxgi_factory->Release( );
    m_d3dDevice->Release( );
    m_immediateDeviceContext->release( );

    if ( m_pixel_shader_blob )
        m_pixel_shader_blob->Release( );

    if ( m_vertex_shader_blob )
        m_vertex_shader_blob->Release( );

    return true;
}

GraphicsEngine* GraphicsEngine::getSingletonGraphEng( ) {
    static GraphicsEngine instance;
    return &instance;
}

SwapChain* GraphicsEngine::initSwapChain( ) {
    return new SwapChain( );
}

VertexBuffer* GraphicsEngine::createVertexBuffer( ) {
    return new VertexBuffer( );
}

bool GraphicsEngine::setPixelShader( ) {
    // set pixel shader
    m_d3dDeviceContext->PSSetShader( m_pixel_shader, nullptr, 0 );

    return true;
}

VertexShader* GraphicsEngine::createVertexShader( const void* pShaderByteCode, size_t pShaderCodeSize ) {
    // create vertex shader instance
    VertexShader* vertexShader = new VertexShader( );

    // release previous shader if it exists
    if ( !vertexShader->init( pShaderByteCode, pShaderCodeSize ) ) {
        vertexShader->release( );
        return nullptr;
    }

    // return vertex shader instance
    return vertexShader;
}

bool GraphicsEngine::compileVertexShader( const wchar_t* pFileName, const char* pEntryPointName, void** pShaderByteCode, size_t* pShaderCodeSize ) {
    try {
        // set HRESULT to 0
        HRESULT hrCompileShader = 0;

        // set error blob to nullptr
        ID3DBlob* errorBlob = nullptr;

        // compile shader from file and store it in blobCode with DX11 Vertex Shader version 5.0
        hrCompileShader = D3DCompileFromFile( pFileName, nullptr, nullptr, pEntryPointName, "vs_5_0", 0, 0, &m_blobCode, &errorBlob );

        // check if shader was compiled
        if ( FAILED( hrCompileShader ) ) {
            if ( errorBlob )
                errorBlob->Release( );

            return false;
        }

        // assign shader byte code and shader code size
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

void GraphicsEngine::releaseCompiledShader( ) {
    if ( m_blobCode )
        m_blobCode->Release( );
}
