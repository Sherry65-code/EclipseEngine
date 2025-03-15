#include "WindowManager.hpp"
#ifdef _WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")

#ifndef DWMA_USE_IMMERSIVE_DARK_MODE
#define DWMA_USE_IMMERSIVE_DARK_MODE 20
#endif
#endif

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

void WindowManager::setWindowResizeCallbackFunction(WindowResizeCallbackFunction wrcf) {
	glfwSetFramebufferSizeCallback(window, wrcf);
}

GLFWwindow* WindowManager::getWindowHandle() {
	return window;
}

#ifdef _WIN32
bool WindowManager::switchDarkMode() {
	HWND hwnd = glfwGetWin32Window(window);
	BOOL darkMode = TRUE;
	HRESULT hr = DwmSetWindowAttribute(hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &darkMode, sizeof(darkMode));
	if (FAILED(hr)) return false;
	return true;
}
#endif

WindowManager::~WindowManager() {
	if (window) {
		glfwDestroyWindow(window);
	}
	glfwTerminate();
}