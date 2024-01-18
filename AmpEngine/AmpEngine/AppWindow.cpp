#include "AppWindow.h"

// create vector struct for specifying world space
struct vect3 {
    // representation of x,y,z (world space)
    float x, y, z;
};

// create vector struct for storing vertex position property
struct vertex {
    vect3 position;
};

AppWindow::AppWindow( ) {
    m_swap_chain = nullptr;
    m_vertex_buffer = nullptr;
    m_vertex_shader = nullptr;
}

AppWindow::~AppWindow( ) {
    // release resources
    if ( m_swap_chain ) {
        m_swap_chain->release( );
    }
    if ( m_vertex_buffer ) {
        m_vertex_buffer->release( );
    }
    if ( m_vertex_shader ) {
        m_vertex_shader->release( );
    }
}

void AppWindow::onCreate( ) {
    try {
        WindowUi::onCreate( );
        // Create the graphics engine and initialize it
        GraphicsEngine::getSingletonGraphEng( )->createAndInit( );
        // Create the swap chain from the factory method in the graphics engine
        m_swap_chain = GraphicsEngine::getSingletonGraphEng( )->createAndInitSwapChain( );
        // get client window size
        RECT rect = this->getClientWindowRect( );
        // init the swap chain with the size of the client window
        //! important: deduct (right - left) and (bottom - top) otherwise the window will be too big and swap chain
        //! will be null
        m_swap_chain->init( this->m_hwnd, rect.right - rect.left, rect.bottom - rect.top );

        // create the vertex list: vert1, vert2, vert3
        // vect {x,y,z}
        vertex vert1 { }, vert2 { }, vert3 = { };
        vert1.position = vect3 { -0.5f, -0.5f, 0.0f };
        vert2.position = vect3 { -0.5f, 0.5f, 0.0f };
        vert3.position = vect3 { 0.5f, -0.5f, 0.0f };

        vertex vertexList[] = { vert1, vert2, vert3, };
        UINT vertexArraySize = ARRAYSIZE( vertexList );

        // create the vertex buffer
        m_vertex_buffer = GraphicsEngine::getSingletonGraphEng( )->createVertexBuffer( );

        // create shaders
        void* shaderByteCode = nullptr;
        size_t shaderByteSize = 0;

        // create shaders in Graphics engine
        GraphicsEngine::getSingletonGraphEng( )->compileVertexShader( L"VertexShader.hlsl", "vsmain", &shaderByteCode, &shaderByteSize );

        // create the vertex shader
        m_vertex_shader = GraphicsEngine::getSingletonGraphEng( )->createVertexShader( shaderByteCode, shaderByteSize );

        // load list of vertices
        m_vertex_buffer->load( vertexList, sizeof( vertex ), vertexArraySize, shaderByteCode, shaderByteSize );

        // release resources
        GraphicsEngine::getSingletonGraphEng( )->releaseCompiledShader( );
    }
    catch ( const std::exception& ex ) {
        LoggingBroker::logException( LoggingBroker::LOG_LEVEL_ERROR, "Failed to create the app window", ex );
        throw;
    }
}

void AppWindow::onUpdate( ) {
    try {
        // set the viewport size
        RECT rect = this->getClientWindowRect( );
        GraphicsEngine::getSingletonGraphEng( )->getImmediateDeviceContext( )->setViewPortSize( ( float )( rect.left - rect.right ), ( float )( rect.bottom - rect.top ) );

        // call set buffer from graphics engine
        GraphicsEngine::getSingletonGraphEng( )->getImmediateDeviceContext( )->setVertexBuffer( m_vertex_buffer );

        // call set shaders
        GraphicsEngine::getSingletonGraphEng( )->getImmediateDeviceContext( )->setVertexShader( m_vertex_shader );

        // Clear the render target
        GraphicsEngine::getSingletonGraphEng( )->getImmediateDeviceContext( )->clearRenderTargetColor( this->m_swap_chain,
                                                                                                    0.0f, 0.3f, 0.4f, 1.0f );

        // call draw triangle list
        GraphicsEngine::getSingletonGraphEng( )->getImmediateDeviceContext( )->DrawTriangleList( m_vertex_buffer->getVericesListCount( ), 0 );

        // Present the back buffer to the screen
        this->m_swap_chain->present( true );

        // call the window ui on update
        WindowUi::onUpdate( );
    }
    catch ( const std::exception& ex ) {
        LoggingBroker::logException( LoggingBroker::LOG_LEVEL_ERROR, "Failed to update the app window", ex );
        throw;
    }
}

void AppWindow::onDestroy( ) {
    WindowUi::onDestroy( );
    // Release the swap chain
    m_swap_chain->release( );
    m_vertex_buffer->release( );
    m_vertex_shader->release( );
    // Release the graphics engine
    GraphicsEngine::getSingletonGraphEng( )->release( );
}
