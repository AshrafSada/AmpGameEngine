#pragma once
#include "WindowUi.h"

class AppWindow : public WindowUi {
public:
    AppWindow( );
    ~AppWindow( );

    // Inherited via WindowUi
    void onCreate( ) override;
    void onUpdate( ) override;
    void onDestroy( ) override;
};
