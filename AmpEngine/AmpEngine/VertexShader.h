#pragma once
#include "GraphicsEngine.h"
#include "LoggingBroker.h"

class GraphicsEngine;

class VertexShader {
public:
    VertexShader( );
    ~VertexShader( );

    void release( );

private:
    bool init( const void* pShaderByteCode, size_t pShaderCodeSize );

private:
    ID3D11VertexShader* m_vertex_shader;

private:
    friend class GraphicsEngine;
};
