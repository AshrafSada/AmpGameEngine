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
}

AppWindow::~AppWindow( ) {
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
        // vect3 {x,y,z}
        vertex vert1, vert2, vert3 = { };
        vert1.position = vect3 { -0.5f, -0.5f, 0.0f };
        vert2.position = vect3 { 0.0f, 0.5f, 0.0f };
        vert3.position = vect3 { 0.5f, -0.5f, 0.0f };

        vertex vertexList[] = { vert1, vert2, vert3, };
        UINT vertexArraySize = ARRAYSIZE( vertexList );

        // create shaders
        void* shaderByteCode = nullptr;
        UINT shaderByteSize = 0;

        // TODO: create shaders in Graphics engine

        // create the vertex buffer
        m_vertex_buffer = GraphicsEngine::getSingletonGraphEng( )->createVertexBuffer( );
        // m_vertex_buffer->load( vertexList,sizeof( vertexArraySize ) , );
    }
    catch ( const std::exception& ex ) {
        LoggingBroker::logException( LoggingBroker::LOG_LEVEL_ERROR, "Failed to create the app window", ex );
        throw;
    }
}

void AppWindow::onUpdate( ) {
    try {
        // get instance of graphics engine
        auto gEngine = GraphicsEngine::getSingletonGraphEng( );

        // set the viewport size
        RECT rect = this->getClientWindowRect( );
        gEngine->getImmediateDeviceContext( )->setViewPortSize( rect.left - rect.right, rect.bottom - rect.top );
        // TODO: call set shaders
        // call set buffer from graphics engine
        gEngine->getImmediateDeviceContext( )->setVertexBuffer( m_vertex_buffer );

        // call draw triangle list
        gEngine->getImmediateDeviceContext( )->DrawTriangleList( m_vertex_buffer->getVericesListCount( ), 0 );

        // Clear the render target
        gEngine->getImmediateDeviceContext( )->clearRenderTargetColor( this->m_swap_chain,
                                                                                                    0, 1, 0, 1 );
        // Present the back buffer to the screen
        this->m_swap_chain->present( false );
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
    // Release the graphics engine
    GraphicsEngine::getSingletonGraphEng( )->release( );
}
