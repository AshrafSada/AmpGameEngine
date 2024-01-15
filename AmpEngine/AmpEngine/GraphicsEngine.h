#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include "ImDeviceContext.h"
#include "SwapChain.h"
#include "VertexBuffer.h"
#include "VertexShader.h"

class ImDeviceContext;
class SwapChain;
class VertexBuffer;
class VertexShader;

class GraphicsEngine {
public:
    // constructor and destructor
    GraphicsEngine( );
    ~GraphicsEngine( );

public:
    // methods
    bool createAndInit( );
    bool release( );

public:
    // getters and setters
    ImDeviceContext* getImmediateDeviceContext( );
    SwapChain* createAndInitSwapChain( );
    VertexBuffer* createVertexBuffer( );
    VertexShader* createVertexShader( const void* pShaderByteCode, size_t pShaderCodeSize );
    bool releaseCompiledShader( );

public:
    // compile commands
    bool compileVertexShader( const wchar_t* pFileName, const char* pEntryPointName, const void** pShaderByteCode, size_t* pShaderCodeSize );

public:
    // singleton instance getter
    static GraphicsEngine* getSingletonGraphEng( );

private:
    ID3D11Device* m_d3dDevice;
    D3D_FEATURE_LEVEL m_featureLevel;
    IDXGIDevice* m_dxgi_device;
    IDXGIAdapter* m_dxgi_adapter;
    IDXGIFactory* m_dxgi_factory;
    ImDeviceContext* m_immediateDeviceContext;
    ID3DBlob* m_blobCode;

private:
    // sub-classes friendship
    friend class SwapChain;
    friend class VertexBuffer;
    friend class VertexShader;
};
