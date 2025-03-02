#pragma once

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_win32.h"

#include <array>

namespace EGL {
	void _INIT_IMGUI(void*, const char*);
	void _START_IMGUI_FRAME();
	void _END_IMGUI_FRAME();
	void _DELETE_IMGUI();

	void _UPDATE_IMGUI_MOUSE_INFO(bool*, int x, int y);
};