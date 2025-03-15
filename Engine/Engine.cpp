#include <Engine/Renderer/Renderer.hpp>
#include <Engine/WindowManager/WindowManager.hpp>
#include <Engine/Standard/IO.hpp>

#include <Engine/FileSystem/FS.hpp>

#include <memory>

void RenderCustomTitleBar(GLFWwindow*);
void WindowResizeCallback(GLFWwindow*, int, int);
void WindowFocusCallback(GLFWwindow*, int);

// Global vars
std::unique_ptr<WindowManager> window_manager;
std::shared_ptr<EclipseRenderer> renderer;

int window_height = -1;
int window_width = -1;
bool darkMode{};
bool isWindowFocused{};

int main() {
	// Fill Window Creation Struct
	WindowManager::WindowCreateInfo window_create_info{};
	window_create_info.title = "Eclipse Engine";
	window_create_info.width = 800;
	window_create_info.height = 600;
	window_create_info.resizable = true;
	window_create_info.fullscreen = false;

	window_width = window_create_info.width;
	window_height = window_create_info.height;
	
	// Initialize window
	window_manager = std::make_unique<WindowManager>();
	if (window_manager->createNewWindow(window_create_info) != ERROR_NONE) {
		io::logMessage(io::LogLevel::ERROR, "Failed to create window!");
		std::exit(EXIT_FAILURE);
	}

	window_manager->setWindowResizeCallbackFunction(WindowResizeCallback);
	glfwSetWindowFocusCallback(window_manager->getWindowHandle(), WindowFocusCallback);

	// Set Mouse move callback function
	//window_manager->setMouseMoveCallbackFunction(mouse_move_callback);
	
	renderer = CreateGLRenderer();
	
	if (!renderer->init_renderer(window_manager->getWindowHandle(), "#version 460")) {
		io::logMessage(io::LogLevel::ERROR, "Failed to intialize renderer!");
		std::exit(EXIT_FAILURE);
	}

	// TEST
	
	// TEST END

	GLFWwindow* pwindow = window_manager->getWindowHandle();

	// Mainloop
	while (!window_manager->shouldClose()) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		renderer->start_ui_recording();

		if (ImGui::Begin("Debugger")) {
			ImGui::Text("Chill mode on");
		}
		ImGui::End();

#ifdef _WIN32
		if (ImGui::Begin("Window Settings")) {
			if (ImGui::Checkbox("Dark Mode", &darkMode))
				window_manager->switchDarkMode(darkMode);
		}
		ImGui::End();
#endif
		renderer->stop_ui_recording();

		window_manager->update();
	}

	renderer->cleanup();
}

void WindowResizeCallback(GLFWwindow* w, int x, int y) {
	window_width = x;
	window_height = y;
}

void WindowFocusCallback(GLFWwindow* w, int f) {
	isWindowFocused = (bool)f;
}