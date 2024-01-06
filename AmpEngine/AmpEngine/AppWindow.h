#pragma once
#include "WindowUi.h"
#include "GraphicsEngine.h"

class AppWindow : public WindowUi {
public:
    AppWindow( );
    ~AppWindow( );

    // Inherited via WindowUi
    void onCreate( ) override;
    void onUpdate( ) override;
    void onDestroy( ) override;
};
