#include "Renderer.hpp"

std::shared_ptr<EclipseRenderer> CreateGLRenderer() {
	std::shared_ptr<EclipseRenderer> renderer = std::make_shared<EclipseRenderer>();
	renderer->init_renderer = &EGL::_INIT;
	renderer->cleanup = &EGL::_DELETE;
	renderer->start_ui_recording = &EGL::_START_IMGUI_FRAME;
	renderer->stop_ui_recording = &EGL::_END_IMGUI_FRAME;
	renderer->pass_mouse_info = &EGL::_UPDATE_IMGUI_MOUSE_INFO;
	return renderer;
}