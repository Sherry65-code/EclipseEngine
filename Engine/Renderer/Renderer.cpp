#include "Renderer.hpp"

std::shared_ptr<EclipseRenderer> CreateGLRenderer() {
	std::shared_ptr<EclipseRenderer> renderer = std::make_shared<EclipseRenderer>();
	renderer->init_renderer = &EGL::_INIT;
	renderer->cleanup = &EGL::_DELETE;
	return renderer;
}