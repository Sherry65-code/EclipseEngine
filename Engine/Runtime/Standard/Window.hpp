#pragma once

#include <string>

namespace Eclipse {

    typedef void (*WindowResizeFunction)(void*, int, int);

    struct WindowCreateInfo {
        std::string title;
        int width;
        int height;
        bool fullscreen;
        bool resizable;
        WindowResizeFunction framebuffer_resize_callback;
    };
}

class Window {
public:
    Window(Eclipse::WindowCreateInfo& window_create_info);
    ~Window();

    bool shouldClose();
    void update();
    bool darkMode(bool dark);
    void* getWindowHandle();
};