#pragma once

#include "GL/GLRenderer.hpp"
#include <memory>

struct EclipseRenderer {
	bool (*init_renderer)();
	bool (*cleanup)();
};

/**
* Create GL Render Device
* @param none
* @return returns render struct for GL
*/
std::shared_ptr<EclipseRenderer> CreateGLRenderer();