#include "VertexBuffer.h"

VertexBuffer::VertexBuffer( ) {
    m_vertext_list = 0;
    m_vertext_size = 0;
    m_buffer_pointer = nullptr;
    m_input_layout = nullptr;
}

VertexBuffer::~VertexBuffer( ) {
}

bool VertexBuffer::load( void* pVerticesList, UINT pVertexSize, UINT pVerticesListSize, void* pShaderByteCode, UINT pShaderCodeSize ) {
    try {
        // release before create to be used many times
        if ( m_input_layout ) {
            m_input_layout->Release( );
        }
        if ( m_buffer_pointer ) {
            m_buffer_pointer->Release( );
        }
        // create buffer description
        D3D11_BUFFER_DESC buffDesc = { };
        buffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER; // bind to vertext buffer in DX11
        buffDesc.ByteWidth = pVertexSize * pVerticesListSize; // buffer memory size
        buffDesc.CPUAccessFlags = 0; // no CPU access required
        buffDesc.Usage = D3D11_USAGE_DEFAULT; // use the GPU
        buffDesc.MiscFlags = 0; // no additional flags needed
        buffDesc.StructureByteStride = 0; // set to 0 for now

        // create sub-resource initial data
        D3D11_SUBRESOURCE_DATA initData = { };
        initData.pSysMem = pVerticesList;

        // assign attributes from params
        m_vertext_size = pVertexSize;
        m_vertext_list = pVerticesListSize;

        // create the buffer using DX11
        auto gEngine = GraphicsEngine::getSingletonGraphEng( );
        HRESULT vBuffHr = gEngine->m_d3dDevice->CreateBuffer( &buffDesc, &initData, &m_buffer_pointer );

        // check if create buffer failed
        if ( FAILED( vBuffHr ) ) {
            return false;
        }

        // create input element description

        // currently using only the position attribute
        D3D11_INPUT_ELEMENT_DESC inputElemDesc[] = {
            // {semantic name, semantic index, DXGI format, input slot, aligned byte offset, input slot classification, Instance Data Step Rate}
            {
                "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0
            }
        };

        UINT inputElemDescSize = ARRAYSIZE( inputElemDesc );

        // create input layout
        HRESULT inputHr = gEngine->m_d3dDevice->CreateInputLayout( inputElemDesc, inputElemDescSize, pShaderByteCode, pShaderCodeSize, &m_input_layout );

        // check if input layout create failed
        if ( FAILED( inputHr ) ) {
            return false;
        }

        return true;
    }
    catch ( const std::exception& ex ) {
        LoggingBroker::logException( LoggingBroker::LOG_LEVEL_ERROR, "VertexBuffer::load( void* pVerticesList, UINT pVertexSize, UINT pVerticesListSize )", ex );
    }
}

bool VertexBuffer::release( ) {
    m_buffer_pointer->Release( );
    m_input_layout->Release( );
    delete this;
    return true;
}
