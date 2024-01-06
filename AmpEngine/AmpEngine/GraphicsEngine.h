#pragma once
#include <d3d11.h>

class GraphicsEngine {
public:
    GraphicsEngine( );
    ~GraphicsEngine( );

    bool Init( );
    bool Release( );

    // singleton instance getter
    static GraphicsEngine* GetInstance( );

private:
    ID3D11Device* m_d3dDevice;
    ID3D11DeviceContext* m_d3dDeviceContext;
    D3D_FEATURE_LEVEL m_featureLevel;
};
