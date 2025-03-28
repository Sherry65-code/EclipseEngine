#include "Window.hpp"

#include <GLFW/glfw3.h>

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

GLFWwindow* pwindow{};

// DID NOT IMPLEMENT FULLSCREEN FEATURE

Window::Window(Eclipse::WindowCreateInfo& window_create_info) {
    if (!glfwInit()) return;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, window_create_info.resizable);

    pwindow = glfwCreateWindow(window_create_info.width, window_create_info.height, window_create_info.title.c_str(), nullptr, nullptr);

    GLFWimage icon{};
    icon.height = window_create_info.icon.height;
    icon.width = window_create_info.icon.width;
    icon.pixels = window_create_info.icon.pixels;

    glfwSetWindowIcon(pwindow, 1, &icon);

    if (window_create_info.framebuffer_resize_callback) {
        glfwSetFramebufferSizeCallback(pwindow, (GLFWframebuffersizefun)window_create_info.framebuffer_resize_callback);
    }
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(pwindow);
}

void Window::update() {
    glfwPollEvents();
}

Window::~Window() {
    if (!pwindow) return;
    glfwDestroyWindow(pwindow);
    glfwTerminate();
}
void* Window::getWindowHandle() {
    return pwindow;
}


#ifdef _WIN32
bool Window::darkMode(bool dark) {
    HWND hwnd = glfwGetWin32Window(pwindow);
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