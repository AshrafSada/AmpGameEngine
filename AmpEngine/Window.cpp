#include "Window.h"

// create a window pointer
Window* window = nullptr;

// Default constructor
Window::Window() {}

// create window procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        // event handler for window creation
        window->onCreate();
        break;
    case WM_UPDATEUISTATE:
        // event handler for window update
        window->onUpdate();
        break;
    case WM_DESTROY:
        // event handler for window destruction
        window->onDestroy();
        ::PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

bool Window::init() {
    // Create the window class
    WNDCLASSEX wcex = { 0 };
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style =
        CS_HREDRAW |
        CS_VREDRAW; // Redraw on horizontal or vertical movement/adjustment
    wcex.lpfnWndProc = WndProc; // Default window procedure
    wcex.hInstance =
        GetModuleHandle(NULL); // Get the handle of the current module
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);     // Load the arrow cursor
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);   // Load the application icon
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION); // Load the application icon
    wcex.hbrBackground =
        (HBRUSH)(COLOR_WINDOW + 1);         // Set the background color to white
    wcex.lpszClassName = L"AmpWindowClass"; // Set the class name
    wcex.lpszMenuName = NULL;               // No menu

    // Register the window class
    if (!::RegisterClassEx(&wcex)) {
        return false;
    }

    // if window is null, set it to this window
    if (!window) {
        window = this;
    }

    // Create the window
    m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"AmpWindowClass",
        L"Amp Sample Game", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
        CW_USEDEFAULT, 1024, 768, NULL, NULL, GetModuleHandle(NULL),
        NULL);

    if (!m_hwnd) {
        return false;
    }

    // Show the window
    ::ShowWindow(m_hwnd, SW_SHOW);

    // Update the window
    ::UpdateWindow(m_hwnd);

    // set the window to run = true
    m_is_run = true;
    return true;
}

bool Window::broadcast()
{
    // Handle the window messages
    MSG msg;

    // PeekMessage will return > 0 if there is a message ready to be processed in windows message queue
    while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0) {
        // Translate virtual-key messages into character messages
        TranslateMessage(&msg);
        // Dispatches a message to a window procedure
        DispatchMessage(&msg);
    }
    // Call the event handler for the window update
    window->onUpdate();
    // Sleep for 1 ms to avoid running the loop too fast
    Sleep(1);

    // Check if the window was closed
    if (msg.message == WM_NULL) {
        if (window) {
            window->release();
            delete window;
            window = NULL;
        }
        if (!IsWindow(m_hwnd)) {
            m_hwnd = NULL; // Message processing loop takes care of destroying this
            UnregisterClass(L"AmpWindowClass", GetModuleHandle(NULL));
            return false;
        }
    }

    return true;
}

bool Window::isRun() {
    return m_is_run;
}

bool Window::release() {
    // Destroy the window
    if (!::DestroyWindow(m_hwnd)) {
        return false;
    }

    return true;
}

void Window::onDestroy()
{
    // set is run to false
    m_is_run = false;
}

Window::~Window() {}
