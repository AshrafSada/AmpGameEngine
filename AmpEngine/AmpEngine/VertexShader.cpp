#include "VertexShader.h"

VertexShader::VertexShader( ) {
    m_vertex_shader = nullptr;
}

VertexShader::~VertexShader( ) {
}

void VertexShader::release( ) {
    if ( m_vertex_shader != nullptr ) {
        m_vertex_shader->Release( );
    }
    delete this;
}

bool VertexShader::init( const void* pShaderByteCode, size_t pShaderCodeSize ) {
    try {
        // get instance of graphics engine
        auto gEngine = GraphicsEngine::getSingletonGraphEng( );

        // create vertex shader using d3d device implemented in graphics engine
        HRESULT cvsHr = gEngine->m_d3dDevice->CreateVertexShader( pShaderByteCode,
                                                                  pShaderCodeSize,
                                                                  nullptr,
                                                                  &m_vertex_shader );
        // check result
        if ( FAILED( cvsHr ) ) {
            return false;
        }

        return true;
    }
    catch ( const std::exception& ex ) {
        LoggingBroker::logException( LoggingBroker::LOG_LEVEL_ERROR,
                                     "VertexShader::init( void* pShaderByteCode, size_t pShaderCodeSize )",
                                     ex );
    }
}
