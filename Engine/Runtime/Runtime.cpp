#include "Runtime.hpp"

#include <Runtime/Standard/Window.hpp>

void EclipseRuntime::Init() {
    // Initialize the runtime
    Eclipse::WindowCreateInfo window_create_info{};
    window_create_info.title = "Hello, World!";
    window_create_info.width = 800;
    window_create_info.height = 600;
    window_create_info.fullscreen = false;
    window_create_info.resizable = false;
    
    Window window(window_create_info);
    window.darkMode(true);

    while (!window.shouldClose()) {
        window.update();
    }
    
}

void EclipseRuntime::Shutdown() {
    // Shutdown the runtime
}