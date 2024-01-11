#include "SwapChain.h"

SwapChain::SwapChain( ) {
    m_swap_chain = { 0 };
    m_rtv = { 0 };
}

SwapChain::~SwapChain( ) {
}

bool SwapChain::init( HWND hwnd, UINT width, UINT height ) {
    try {
        // get device from GraphicsEngine
        ID3D11Device* device = GraphicsEngine::getSingletonGraphEng( )->m_d3dDevice;
        DXGI_SWAP_CHAIN_DESC swap_chain_desc;
        // Free memory for swap_chain_desc to avoid read access violation
        ZeroMemory( &swap_chain_desc, sizeof( swap_chain_desc ) );
        // set buffer count for swap chain desc (front and back buffer)
        swap_chain_desc.BufferCount = 1; // front buffer
        // set width and height of back buffer
        swap_chain_desc.BufferDesc.Width = width;
        swap_chain_desc.BufferDesc.Height = height;
        // set pixel format for back buffer to 8 bits per channel RGBA
        swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        // set refresh rate to 60 Hz
        swap_chain_desc.BufferDesc.RefreshRate.Numerator = 60;
        // set the refresh rate denominator to 1 (60/1 = 60 Hz)
        swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
        // set the usage of the back buffer to render target output
        swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        // set the handle for the window to render to
        swap_chain_desc.OutputWindow = hwnd;
        // turn multisampling off
        swap_chain_desc.SampleDesc.Count = 1;
        // set multisampling quality level to 0 (no quality)
        swap_chain_desc.SampleDesc.Quality = 0;
        // set to windowed mode
        swap_chain_desc.Windowed = TRUE;

        // create swap chain using factory method from GraphicsEngine
        HRESULT hrSwapResult = GraphicsEngine::getSingletonGraphEng( )->m_dxgi_factory->CreateSwapChain( device,
            &swap_chain_desc,
            &m_swap_chain );

        // check if swap chain was created successfully before creating render target view
        if ( SUCCEEDED( hrSwapResult ) ) {
            ID3D11Texture2D* back_buffer = nullptr;
            m_swap_chain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( void** )&back_buffer );
            // create render target view using back buffer
            if ( back_buffer != nullptr ) {
                device->CreateRenderTargetView( back_buffer, NULL, &m_rtv );
            }
            // free memory for back buffer
            back_buffer->Release( );
            return true;
        }
        else {
            return false;
        }

        return true;
    }
    catch ( const std::exception& ex ) {
        LoggingBroker::logException( LoggingBroker::LOG_LEVEL_ERROR, "SwapChain::Init( HWND hwnd, UINT width, UINT height )", ex );
        return false;
    }
}

bool SwapChain::present( bool vsync ) {
    try {
        // present the back buffer to the screen
        if ( m_swap_chain == nullptr )
            return false;
        m_swap_chain->Present( vsync, NULL );
        return true;
    }
    catch ( const std::exception& ex ) {
        LoggingBroker::logException( LoggingBroker::LOG_LEVEL_ERROR, "SwapChain::Present( bool vsync )", ex );
        return false;
    }
}

bool SwapChain::release( ) {
    //! HACK: check swap chain memory state to avoid read access violation
    if ( m_swap_chain == nullptr ) {
        return false;
    }
    m_swap_chain->Release( );
    delete this;
    return true;
}
