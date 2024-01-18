#include "WindowUi.h"

// create a window pointer
WindowUi* g_window = nullptr;

const LPCWSTR WINDOW_CLASS_NAME = L"AmpEngineWindowClass";
// WindowProc is a callback function that handles messages sent to a window
static LRESULT CALLBACK WindowProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) {
    // sort through and find what code to run for the message given
    switch ( uMsg ) {
        case WM_CREATE:
        {
            // collect events fired when the window is created
            WindowUi* window = ( WindowUi* )( ( LPCREATESTRUCT )lParam )->lpCreateParams;
            // store the window pointer in the window class for later use
            SetWindowLongPtr( hwnd, GWLP_USERDATA, ( LONG_PTR )window );
            // call set hwnd to set the window event handlers before the window is created
            g_window->setHwnd( hwnd );
            // this message is read when the window is created
            g_window->onCreate( );
            return 0;
        }
        // this message is read when the window is closed
        case WM_DESTROY:
        {
            // collect events fired when the window is destroyed
            WindowUi* window = ( WindowUi* )GetWindowLongPtr( hwnd, GWLP_USERDATA );
            // close the application entirely
            g_window->onDestroy( );
            PostQuitMessage( 0 );
            return 0;
        } break;
        default:
            return DefWindowProc( hwnd, uMsg, wParam, lParam );
    }

    return 0;
}

WindowUi::WindowUi( ) {
    m_hwnd = NULL;
    m_is_running = false;
    g_window = this;
}

bool WindowUi::init( ) {
    // create the window class
    WNDCLASSEX wc;
    wc.cbSize = sizeof( WNDCLASSEX );
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = GetModuleHandle( NULL );
    wc.hIcon = NULL;
    wc.hCursor = LoadCursor( NULL, IDC_ARROW );
    wc.hbrBackground = ( HBRUSH )COLOR_WINDOW;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = WINDOW_CLASS_NAME;
    wc.hIconSm = NULL;

    // register the window class
    RegisterClassEx( &wc );

    // set windowUi pointer to this
    if ( !g_window ) {
        g_window = this;
    }

    // create the window and use the result as the handle
    m_hwnd = CreateWindowEx( NULL,
                            WINDOW_CLASS_NAME,     // name of the window class
                            L"Amp Game Engine",    // title of the window
                            WS_OVERLAPPEDWINDOW,   // window style
                            CW_USEDEFAULT,         // position x of the window
                            CW_USEDEFAULT,         // position y of the window
                            1024,                  // width of the window
                            768,                   // height of the window
                            NULL,                  // we have no parent window, NULL
                            NULL,                  // we aren't using menus, NULL
                            GetModuleHandle( NULL ), // application handle
                            NULL );                 // used with multiple windows, NULL

    // check if window creation failed
    if ( !m_hwnd ) {
        return false;
    }

    // display the window on the screen
    ShowWindow( m_hwnd, SW_SHOW );

    // update the window
    UpdateWindow( m_hwnd );

    // set running to true
    m_is_running = true;

    return true;
}

bool WindowUi::isRunning( ) {
    return m_is_running;
}

// this function handles the message loop
bool WindowUi::broadcast( ) {
    // call the update function
    this->onUpdate( );
    MSG msg;

    // peek at the next message, remove it from the queue
    while ( PeekMessage( &msg, m_hwnd, NULL, NULL, PM_REMOVE ) ) {
        // translate keystroke messages into character messages
        TranslateMessage( &msg );
        // dispatch the message to the window procedure
        DispatchMessage( &msg );
    }

    // relax the CPU for a 1ms
    Sleep( 1 );

    // check if the message queue is empty
    if ( msg.message == WM_NULL ) {
        // release the window if still running
        if ( g_window ) {
            g_window->release( );
            delete g_window;
            g_window = nullptr;
        }
        // check if the window class is still registered
        if ( !IsWindow( m_hwnd ) ) {
            g_window = nullptr;
            // unregister the window class
            UnregisterClass( WINDOW_CLASS_NAME, GetModuleHandle( NULL ) );
            return false;
        }
    }

    return true;
}

bool WindowUi::release( ) {
    // check if the window is not destroyed
    if ( !DestroyWindow( m_hwnd ) ) {
        return false;
    }
    return true;
}

void WindowUi::onDestroy( ) {
    // set is_running to false
    m_is_running = false;
}

WindowUi::~WindowUi( ) {
}

RECT WindowUi::getClientWindowRect( ) {
    RECT rc;
    GetClientRect( this->m_hwnd, &rc );

    return rc;
}

void WindowUi::setHwnd( HWND hwnd ) {
    this->m_hwnd = hwnd;
}
