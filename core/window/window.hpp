#pragma once

#include <string>
#include <GLFW/glfw3.h>
#include <io/io.hpp>

class Window {
public:
	typedef GLFWwindow* window_t;

	Window(std::string title, uint32_t width, uint32_t height, bool isResizable, bool isFullscreen);
	~Window();

	bool shouldWindowClose();
	window_t returnWindowInstance();
};