#include "window.hpp"

Window::window_t window_instance;

Window::Window(std::string title, uint32_t width, uint32_t height, bool isResizable, bool isFullscreen) {
	// Init GLFW
	if (!glfwInit())
		io::printErrorAndExit("Failed to initialize GLFW!");

	// Resizable
	glfwWindowHint(GLFW_RESIZABLE, isResizable);

	window_instance = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

	if (!window_instance) {
		io::printError("Failed to create window!");
		glfwTerminate();
		return;
	}
}

bool Window::shouldWindowClose() {
	return glfwWindowShouldClose(window_instance);
}

Window::window_t Window::returnWindowInstance() {
	return window_instance;
}

Window::~Window() {
	if (window_instance != nullptr) glfwTerminate();
}