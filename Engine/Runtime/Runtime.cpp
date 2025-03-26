#include "Runtime.hpp"

#include <Runtime/Standard/Window.hpp>
#include <Runtime/Driver/VK/VulkanMain.hpp>
#include <Runtime/Standard/IO.hpp>

#include <memory>

std::shared_ptr<Window> window{};
std::unique_ptr<evk> driver{};

static void FRAMEBUFFER_RESIZE_FUNCTION(void* window, int width, int height) {
    driver->updateFramebuffer();
}

void EclipseRuntime::Init() {
    // Initialize the runtime
    Eclipse::WindowCreateInfo window_create_info{};
    window_create_info.title = "Eclipse Engine Demo";
    window_create_info.width = 800;
    window_create_info.height = 600;
    window_create_info.fullscreen = false;
    window_create_info.resizable = true;
    window_create_info.framebuffer_resize_callback = FRAMEBUFFER_RESIZE_FUNCTION;
    window_create_info.icon = EclipseFileSystem::LoadRawImageFromFile("Resources/icon.png");
    
    window = std::make_shared<Window>(window_create_info);
    window->darkMode(true);

    // Vulkan Init
    driver = std::make_unique<evk>();
    
    try {
        driver->passWindowPointer(window->getWindowHandle());
        driver->initalizeDriver();
    }
    catch (const std::runtime_error& re) {
        const std::string runtime_message = re.what();
        io::logMessage(io::LogLevel::ERROR, "{}", runtime_message);
    }

    while (!window->shouldClose()) {
        window->update();
        driver->drawFrame();
    }
}

void EclipseRuntime::Shutdown() {
    // Shutdown the runtime
}