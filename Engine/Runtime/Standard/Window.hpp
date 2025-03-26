#pragma once

#include <string>
#include <Runtime/Filesystem/FileSystem.hpp>

namespace Eclipse {

    typedef void (*WindowResizeFunction)(void*, int, int);

    struct WindowCreateInfo {
        std::string title;
        int width;
        int height;
        bool fullscreen;
        bool resizable;
        RawImage icon;
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