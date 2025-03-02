#include <Engine/WindowManager/WindowManager.hpp>
#include <Engine/Renderer/Renderer.hpp>
#include <Engine/Standard/IO.hpp>

#include <memory>

// Global vars
std::unique_ptr<WindowManager> window_manager;
std::shared_ptr<EclipseRenderer> renderer;

int main() {
	// Fill Window Creation Struct
	WindowManager::WindowCreateInfo window_create_info{};
	window_create_info.title = "Eclipse Engine";
	window_create_info.width = 800;
	window_create_info.height = 600;
	window_create_info.resizable = true;
	window_create_info.fullscreen = false;
	
	// Initialize window
	window_manager = std::make_unique<WindowManager>();
	if (!window_manager->createNewWindow(window_create_info)) {
		io::logMessage(io::LogLevel::EERROR, "Failed to create window!");
		std::exit(EXIT_FAILURE);
	}

	// Initialize OpenGL Context
	if (!window_manager->createGLContext()) {
		io::logMessage(io::LogLevel::EERROR, "Failed to create OpenGL Context!");
		std::exit(EXIT_FAILURE);
	}

	renderer = CreateGLRenderer();
	
	if (!renderer->init_renderer()) {
		io::logMessage(io::LogLevel::EERROR, "Failed to intialize renderer!");
		std::exit(EXIT_FAILURE);
	}

	// Mainloop
	while (!window_manager->shouldClose()) {
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		window_manager->update();
	}

	renderer->cleanup();
}