#pragma once
#include "GraphicsEngine.h"
#include <system_error>
#include "LoggingBroker.h"

class VertexBuffer {
public:
    // constructor and destructor
    VertexBuffer( );
    ~VertexBuffer( );
public:
    // methods
    bool load( void* pVerticesList, UINT pVertexSize, UINT pVerticesListSize, void* pShaderByteCode, UINT pShaderCodeSize );
    bool release( );

private:
    // attributes
    UINT m_vertext_size;
    UINT m_vertext_list;
    ID3D11Buffer* m_output_buffer;
    ID3D11InputLayout* m_input_layout;
};
