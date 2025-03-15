#pragma once
#include "Ext/glad/glad.h"

#include "GLUI.hpp"

namespace EGL {
	bool _INIT(GLFWwindow*, const char*);
	bool _DELETE();
};