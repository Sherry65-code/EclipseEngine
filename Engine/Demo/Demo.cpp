#include <Runtime/Window/Window.hpp>
#include <Runtime/FileSystem/FileSystem.hpp>
#include <Runtime/Drivers/DriverDispatcher.hpp>
#include <Runtime/Standard/IO.hpp>

#include <memory>

std::unique_ptr<Window> window{};
std::unique_ptr<Driver> driver{};

int main() {
    Eclipse::WindowCreateInfo window_create_info{};
    window_create_info.title = "Eclipse Engine Demo";
    window_create_info.width = 800;
    window_create_info.height = 600;
    window_create_info.fullscreen = false;
    window_create_info.resizable = true;
    window_create_info.icon = EclipseFileSystem::LoadRawImageFromFile("Resources/favicon.png");
    window_create_info.framebuffer_resize_callback = nullptr;

    try {
        window = std::make_unique<Window>(window_create_info);
        driver = DriverDispatcher::DispatchDriver(Eclipse::DriverType::OpenGL);
        
        void* winptr = window->getWindowHandle();
        driver->Initialize(winptr);

        while (!window->shouldClose()) {
            driver->UpdateFrame();
            window->update();
        }
    } catch (const std::exception& err) {
        std::string out = err.what();
        io::logMessage(io::LogLevel::ERROR, "{}", out);
    }
}