#include <Engine/Renderer/Renderer.hpp>
#include <Engine/WindowManager/WindowManager.hpp>
#include <Engine/Standard/IO.hpp>

#include <Engine/FileSystem/FS.hpp>

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
	if (window_manager->createNewWindow(window_create_info) != ERROR_NONE) {
		io::logMessage(io::LogLevel::ERROR, "Failed to create window!");
		std::exit(EXIT_FAILURE);
	}

	// Set Mouse move callback function
	//window_manager->setMouseMoveCallbackFunction(mouse_move_callback);
	
	renderer = CreateGLRenderer();
	
	if (!renderer->init_renderer(window_manager->getWindowHandle(), "#version 460")) {
		io::logMessage(io::LogLevel::ERROR, "Failed to intialize renderer!");
		std::exit(EXIT_FAILURE);
	}

	// TEST
	
	// TEST END

	// Mainloop
	while (!window_manager->shouldClose()) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		renderer->start_ui_recording();

		if (ImGui::Begin("Debugger")) {
			ImGui::Text("Chill mode on");
		}
		ImGui::End();

		renderer->stop_ui_recording();

		window_manager->update();
	}

	renderer->cleanup();
}