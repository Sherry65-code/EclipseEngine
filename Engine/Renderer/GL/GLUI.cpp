#include "GLUI.hpp"

void EGL::_INIT_IMGUI(void* HWND, const char* gl_version) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable keyboard controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable gamepad controls
	//io.MousePos

	ImGui_ImplWin32_Init(HWND);
	ImGui_ImplOpenGL3_Init(gl_version);
}

void EGL::_START_IMGUI_FRAME() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void EGL::_END_IMGUI_FRAME() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void EGL::_DELETE_IMGUI() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void EGL::_UPDATE_IMGUI_MOUSE_INFO(bool* mousebuttons, int x, int y) {
	ImGuiIO& io = ImGui::GetIO();
	io.MousePos = ImVec2((float)x, (float)y);
	for (int i = 0; i < 3; i++) {
		io.MouseDown[i] = mousebuttons[i];
	}
}