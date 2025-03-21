#include "Runtime.hpp"

#include <Runtime/Standard/Window.hpp>
#include <Runtime/Driver/VK/VulkanMain.hpp>
#include <Runtime/Standard/IO.hpp>

#include <memory>

std::shared_ptr<Window> window{};
std::shared_ptr<evk> driver{};

void EclipseRuntime::Init() {
    // Initialize the runtime
    Eclipse::WindowCreateInfo window_create_info{};
    window_create_info.title = "Hello, World!";
    window_create_info.width = 800;
    window_create_info.height = 600;
    window_create_info.fullscreen = false;
    window_create_info.resizable = false;
    
    window = std::make_shared<Window>(window_create_info);
    window->darkMode(true);

    // Vulkan Init
    driver = std::make_shared<evk>();
    
    try {
        driver->createInstance();
        driver->pickPhysicalDevice();
        driver->createLogicalDevice();
    }
    catch (const std::exception& exception) {
        const std::string exception_message = exception.what();
        io::logMessage(io::LogLevel::ERROR, "{}", exception_message);
    }

    //while (!window->shouldClose()) {
    //    window->update();
    //}
}

void EclipseRuntime::Shutdown() {
    // Shutdown the runtime
}