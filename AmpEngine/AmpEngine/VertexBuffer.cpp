#include "VertexBuffer.h"

VertexBuffer::VertexBuffer( ) {
    m_vertext_list = 0;
    m_vertext_size = 0;
    m_buffer_pointer = nullptr;
    m_input_layout = nullptr;
}

VertexBuffer::~VertexBuffer( ) {
}

bool VertexBuffer::load( void* pVerticesList, UINT pVertexSize, UINT pVerticesListSize, void* pShaderByteCode, size_t pShaderCodeSize ) {
    try {
        // release before create to be used many times
        if ( m_buffer_pointer ) {
            m_buffer_pointer->Release( );
        }
        if ( m_input_layout ) {
            m_input_layout->Release( );
        }

        // create buffer description
        D3D11_BUFFER_DESC buffDesc = { };
        buffDesc.Usage = D3D11_USAGE_DEFAULT;
        buffDesc.ByteWidth = pVertexSize * pVerticesListSize;
        buffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        buffDesc.CPUAccessFlags = 0;
        buffDesc.MiscFlags = 0;

        // create sub-resource initial data
        D3D11_SUBRESOURCE_DATA initData = { };
        initData.pSysMem = pVerticesList;

        // assign attributes from params
        m_vertext_size = pVertexSize;
        m_vertext_list = pVerticesListSize;

        // create buffer
        HRESULT hr = GraphicsEngine::getSingletonGraphEng( )->m_d3dDevice->CreateBuffer( &buffDesc, &initData, &m_buffer_pointer );

        // check if buffer was created
        if ( FAILED( hr ) ) {
            return false;
        }

        // create input layout description
        D3D11_INPUT_ELEMENT_DESC layoutDesc[] = {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA },
            { "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA }
        };

        // get input layout size
        UINT size = ARRAYSIZE( layoutDesc );

        // create input layout
        hr = GraphicsEngine::getSingletonGraphEng( )->m_d3dDevice->CreateInputLayout( layoutDesc, size, pShaderByteCode, pShaderCodeSize, &m_input_layout );

        // check if input layout was created
        if ( FAILED( hr ) ) {
            return false;
        }

        return true;
    }
    catch ( const std::exception& ex ) {
        LoggingBroker::logException( LoggingBroker::LOG_LEVEL_ERROR,
                                     "VertexBuffer::load( void* pVerticesList, UINT pVertexSize, UINT pVerticesListSize )", ex );
    }

    return true;
}

UINT VertexBuffer::getVericesListCount( ) {
    return this->m_vertext_list;
}

bool VertexBuffer::release( ) {
    if ( m_input_layout ) {
        m_input_layout->Release( );
        return false;
    }
    if ( m_buffer_pointer != nullptr ) {
        m_buffer_pointer->Release( );
    }
    delete this;
    return true;
}
