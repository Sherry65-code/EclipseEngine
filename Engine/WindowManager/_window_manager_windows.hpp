#include "WindowManager.hpp"

#include <Windows.h>
#include <Engine/Standard/IO.hpp>
#include <gl/GL.h>

#pragma comment(lib, "opengl32.lib")

const char g_szClassName[] = "windew";
HWND hwnd;
MSG Msg;
HDC hdc;
HGLRC hglrc;
bool quit;
bool gl;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

bool WindowManager::createNewWindow(WindowCreateInfo& window_create_info) {
	WNDCLASSEX wc;
	HINSTANCE hInstance = GetModuleHandle(NULL);
	int nCmdShow = SW_SHOWDEFAULT;

	// Register window class
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc)) {
        io::logMessage(io::LogLevel::EDEBUG, "Failed to register window class!");
        return false;
    }

    // Create Window
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE, 
        g_szClassName, 
        window_create_info.title.c_str(), 
        WS_OVERLAPPEDWINDOW, 
        CW_USEDEFAULT, 
        CW_USEDEFAULT, 
        window_create_info.width, 
        window_create_info.height, 
        NULL, 
        NULL, 
        hInstance, 
        NULL
    );

    if (hwnd == NULL) {
        io::logMessage(io::LogLevel::EDEBUG, "Failed to create window!");
        return false;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    return true;
}

void WindowManager::update() {
    while (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE)) {
        if (Msg.message == WM_QUIT) {
            quit = true;
        }
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
}

bool WindowManager::shouldClose() {
    return quit;
}

bool WindowManager::createGLContext() {
    gl = true;

    // Get Device context
    hdc = GetDC(hwnd);

    // set pixl format
    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        32,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        24,
        8,
        0,
        PFD_MAIN_PLANE,
        0,
        0,
        0,
        0
    };

    int pixelFormat = ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc, pixelFormat, &pfd);

    // Create opengl renderering context
    hglrc = wglCreateContext(hdc);
    wglMakeCurrent(hdc, hglrc);

    if (!hglrc) {
        io::logMessage(io::LogLevel::EDEBUG, "Failed to create opengl context!");
        return false;
    }

    return true;
}

WindowManager::~WindowManager() {
    if (hwnd != NULL) {
        DestroyWindow(hwnd);
        hwnd = NULL;
        if (gl) {
            wglMakeCurrent(NULL, NULL);
            wglDeleteContext(hglrc);
            ReleaseDC(hwnd, hdc);
        }
    }
    UnregisterClass(g_szClassName, GetModuleHandle(NULL));
}