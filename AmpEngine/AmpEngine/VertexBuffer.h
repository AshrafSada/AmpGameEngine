#pragma once
#include "GraphicsEngine.h"
#include <system_error>
#include "LoggingBroker.h"
#include "ImDeviceContext.h"

class ImDeviceContext;

class VertexBuffer {
public:
    // constructor and destructor
    VertexBuffer( );
    ~VertexBuffer( );
public:
    // methods
    bool load( void* pVerticesList, UINT pVertexSize, UINT pVerticesListSize, void* pShaderByteCode, size_t pShaderCodeSize );
    UINT getVericesListCount( );
    bool release( );

private:
    // attributes
    UINT m_vertext_size;
    UINT m_vertext_list;
    ID3D11Buffer* m_buffer_pointer;
    ID3D11InputLayout* m_input_layout;
private:
    friend class ImDeviceContext;
};
