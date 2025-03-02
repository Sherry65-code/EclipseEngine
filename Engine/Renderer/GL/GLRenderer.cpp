#include "GLRenderer.hpp"
#include <Engine/Standard/IO.hpp>
#include <windows.h>

bool EGL::_INIT() {
	
	if (!gladLoadGL()) {
		io::logMessage(io::LogLevel::EDEBUG, "gladLoadGL failed!");
		return false;
	}

	return true;
}

bool EGL::_DELETE() {

	return true;
}