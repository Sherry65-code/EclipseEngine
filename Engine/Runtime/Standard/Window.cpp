#include "Window.hpp"

#include <glfw/glfw3.h>

#ifdef _WIN32

#ifndef GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#endif

#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")
#include <glfw/glfw3native.h>
#ifndef DWMA_USE_IMMERSIVE_DARK_MODE
#define DWMA_USE_IMMERSIVE_DARK_MODE 20
#endif

#endif

GLFWwindow* window{};

// DID NOT IMPLEMENT FULLSCREEN FEATURE

Window::Window(Eclipse::WindowCreateInfo& window_create_info) {
    if (!glfwInit()) return;

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, window_create_info.resizable);

    window = glfwCreateWindow(window_create_info.width, window_create_info.height, window_create_info.title.c_str(), nullptr, nullptr);

    if (window_create_info.framebuffer_resize_callback) {
        glfwSetFramebufferSizeCallback(window, (GLFWframebuffersizefun)window_create_info.framebuffer_resize_callback);
    }
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(window);
}

void Window::update() {
    glfwPollEvents();
}

Window::~Window() {
    if (!window) return;
    glfwDestroyWindow(window);
    glfwTerminate();
}
void* Window::getWindowHandle() {
    return window;
}


#ifdef _WIN32
bool Window::darkMode(bool dark) {
    HWND hwnd = glfwGetWin32Window(window);
    BOOL darkMode = dark;
    HRESULT hr = DwmSetWindowAttribute(hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &darkMode, sizeof(darkMode));
    if (FAILED(hr)) return false;
    return true;
}
#else
bool Window::darkMode(bool dark) {
    return false;
}
#endif