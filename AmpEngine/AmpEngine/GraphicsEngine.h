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
    bool init( );
    bool release( );

public:
    // compile vertex shader and release compiled shader
    VertexShader* createVertexShader( const void* pShaderByteCode, size_t pShaderCodeSize );
    bool compileVertexShader( const wchar_t* pFileName, const char* pEntryPointName, void** pShaderByteCode, size_t* pShaderCodeSize );
    void releaseCompiledShader( );

public:
    // methods to create and initialize sub-classes
    ImDeviceContext* getImmediateDeviceContext( );
    SwapChain* initSwapChain( );
    VertexBuffer* createVertexBuffer( );
    bool setPixelShader( );

public:
    // singleton instance getter
    static GraphicsEngine* getSingletonGraphEng( );

private:
    // private attributes
    D3D_FEATURE_LEVEL m_featureLevel;
    ID3D11Device* m_d3dDevice;
    IDXGIAdapter* m_dxgi_adapter;
    IDXGIDevice* m_dxgi_device;
    IDXGIFactory* m_dxgi_factory;
    ImDeviceContext* m_immediateDeviceContext;
    ID3D11DeviceContext* m_d3dDeviceContext;

private:
    // ID3D Blobs
    ID3DBlob* m_blobCode;
    ID3DBlob* m_vertex_shader_blob;
    ID3DBlob* m_pixel_shader_blob;

private:
    // private shaders
    ID3D11VertexShader* m_vertex_shader;
    ID3D11PixelShader* m_pixel_shader;

private:
    // sub-classes friendship
    friend class SwapChain;
    friend class VertexBuffer;
    friend class VertexShader;
};
