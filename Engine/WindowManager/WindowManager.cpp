#include "WindowManager.hpp"

static GLFWwindow* window = nullptr;

b32 WindowManager::createNewWindow(WindowCreateInfo& window_create_info) {
	// Check for initialization
	if (!glfwInit()) {
		return ERROR_WINDOW_CREATION_FAILED;
	}

	// Set window hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window
	switch (window_create_info.fullscreen) {
		case true:
			window = glfwCreateWindow(window_create_info.width, window_create_info.height, window_create_info.title.c_str(), glfwGetPrimaryMonitor(), NULL);
			break;
		case false:
			window = glfwCreateWindow(window_create_info.width, window_create_info.height, window_create_info.title.c_str(), NULL, NULL);
			break;
	}

	// Check for window creation
	if (!window) {
		glfwTerminate();
		return ERROR_WINDOW_CREATION_FAILED;
	}

	return ERROR_NONE;
}

void WindowManager::update() {
	glfwSwapBuffers(window);
	glfwPollEvents();
}

bool WindowManager::shouldClose() {
	return glfwWindowShouldClose(window);
}

void WindowManager::setMouseMoveCallbackFunction(MouseMoveCallbackFunction mmcf) {

}

GLFWwindow* WindowManager::getWindowHandle() {
	return window;
}

WindowManager::~WindowManager() {
	if (window) {
		glfwDestroyWindow(window);
	}
	glfwTerminate();
}