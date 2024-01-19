#pragma once
#include "WindowUi.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "ImDeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"

#include <exception>
#include "LoggingBroker.h"

class AppWindow : public WindowUi {
public:
    AppWindow( );
    ~AppWindow( );

    // Inherited via WindowUi
    virtual void onCreate( ) override;
    virtual void onUpdate( ) override;
    virtual void onDestroy( ) override;

private:
    SwapChain* m_swap_chain;
    VertexBuffer* m_vertex_buffer;
    VertexShader* m_vertex_shader;
};
