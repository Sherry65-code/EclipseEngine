#include <string>

namespace Eclipse {
    struct WindowCreateInfo {
        std::string title;
        int width;
        int height;
        bool fullscreen;
        bool resizable;
    };
}

class Window {
public:
    Window(Eclipse::WindowCreateInfo& window_create_info);
    ~Window();

    bool shouldClose();
    void update();
    bool darkMode(bool dark);
};