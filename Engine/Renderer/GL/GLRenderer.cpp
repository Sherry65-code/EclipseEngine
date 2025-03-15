#include "GLRenderer.hpp"
#include <Engine/Standard/IO.hpp>
#include <GLFW/glfw3.h>

bool EGL::_INIT(GLFWwindow* pwindow, const char* gl_version) {
	
	glfwMakeContextCurrent(pwindow);

	if (!gladLoadGL()) {
		io::logMessage(io::LogLevel::DEBUG, "gladLoadGL failed!");
		return false;
	}

	// initialize imgui
	_INIT_IMGUI(pwindow, gl_version);

	return true;
}

bool EGL::_DELETE() {

	_DELETE_IMGUI();

	return true;
}