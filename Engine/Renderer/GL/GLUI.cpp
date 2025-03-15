#include "GLUI.hpp"

#include <Engine/FileSystem/FS.hpp>
#include <Engine/Standard/IO.hpp>

void EGL::_INIT_IMGUI(GLFWwindow* pwindow, const char* gl_version) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable keyboard controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable gamepad controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable docking
	
	const std::string font_loc = "../Engine/Fonts/Regular/SofiaSans.ttf";
	std::vector<char> font_file = efs::readFileAsBinary(font_loc);
	void* font_data = font_file.data();
	int font_data_size = font_file.size();
	if (font_file.empty()) {
		io::logMessage(io::LogLevel::ERROR, "Failed to load font file at \"{}\"! Switching to fallback font!", font_loc);
	}
	else {
		ImFontConfig fontConfig;
		fontConfig.FontDataOwnedByAtlas = false;

		ImFont* customFont = io.Fonts->AddFontFromMemoryTTF(font_data, font_data_size, 15.0f, &fontConfig);

		if (!customFont) {
			io::logMessage(io::LogLevel::ERROR, "Failed to load font! Switching to fallback font!");
		}

		io.Fonts->Build();
	}
	
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(pwindow, true);
	ImGui_ImplOpenGL3_Init(gl_version);
}

void EGL::_START_IMGUI_FRAME() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void EGL::_END_IMGUI_FRAME() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void EGL::_DELETE_IMGUI() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void EGL::_UPDATE_IMGUI_MOUSE_INFO(bool* mousebuttons, int x, int y) {
	ImGuiIO& io = ImGui::GetIO();
	io.MousePos = ImVec2((float)x, (float)y);
	for (int i = 0; i < 3; i++) {
		io.MouseDown[i] = mousebuttons[i];
	}
}