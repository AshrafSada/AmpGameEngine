#pragma once
#include <Windows.h>

class WindowUi {
public:
    WindowUi( );

    bool init( );
    bool broadcast( );
    bool isRunning( );
    bool release( );

    // HACK: declare virtual event handlers as pure virtual functions with empty bodies
    // virtual event handlers = 0 will not link to the base class
    // except for the one implemented in the base class
    virtual void onCreate( ) {
    };
    virtual void onUpdate( ) {
    };
    // implemented in the base class and can be overridden in the derived class
    virtual void onDestroy( );

    ~WindowUi( );

public:
    RECT getClientWindowRect( );
    // Set window event handlers
    void setHwnd( HWND hwnd );

protected:
    HWND m_hwnd;
    bool m_is_running;
};
