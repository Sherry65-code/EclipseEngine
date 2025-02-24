#include <Engine/WindowManager/WindowManager.hpp>

#include <memory>

std::unique_ptr<WindowManager> window_manager;

int main() {
	WindowManager::WindowCreateInfo window_create_info{};
	window_create_info.title = "Eclipse Engine";
	window_create_info.width = 800;
	window_create_info.height = 600;
	window_create_info.resizable = true;
	window_create_info.fullscreen = false;

	window_manager = std::make_unique<WindowManager>();
	window_manager->createNewWindow(window_create_info);

	while (!window_manager->shouldClose()) {
		window_manager->update();
	}
}