#pragma once
#include "GraphicsEngine.h"
#include "LoggingBroker.h"
#include "ImDeviceContext.h"

class GraphicsEngine;
class ImDeviceContext;

class VertexShader {
public:
    VertexShader( );
    ~VertexShader( );
    bool release( );

private:
    bool init( const void* pShaderByteCode, size_t pShaderCodeSize );

private:
    ID3D11VertexShader* m_vertex_shader;

private:
    friend class GraphicsEngine;
    friend class ImDeviceContext;
};
