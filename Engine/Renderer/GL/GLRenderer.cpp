#include "GLRenderer.hpp"
#include <Engine/Standard/IO.hpp>
//#include <windows.h>

bool EGL::_INIT(void* HWND, const char* gl_version) {
	
	if (!gladLoadGL()) {
		io::logMessage(io::LogLevel::EDEBUG, "gladLoadGL failed!");
		return false;
	}

	// initialize imgui
	_INIT_IMGUI(HWND, gl_version);

	return true;
}

bool EGL::_DELETE() {

	_DELETE_IMGUI();

	return true;
}