#pragma once
#include "WindowUi.h"

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
};
