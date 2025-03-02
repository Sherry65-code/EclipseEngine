#pragma once

#include "GL/GLRenderer.hpp"
#include <memory>

struct EclipseRenderer {
	/**
	* Initializes renderer
	* @param hwnd: Window handle version: opengl version (for example: "#version 330")
	* @return did initalization succeed
	*/
	bool (*init_renderer)(void* hwnd, const char* version);
	/**
	Starts frame for UI
	*/
	void (*start_ui_recording)();
	/**
	Render's frame data for UI
	*/
	void (*stop_ui_recording)();
	/**
	* De-Initializes renderer
	* @param none
	* @return did de-initalization succeed
	*/
	bool (*cleanup)();
	/**
	* Passes mouse information to UI
	* @param mousebuttons: array for mouse down info, x: x coord mouse position, y: y coord mouse position
	* @return void
	*/
	void (*pass_mouse_info)(bool* mousebuttons, int x, int y);
};

/**
* Create GL Render Device
* @param none
* @return returns render struct for GL
*/
std::shared_ptr<EclipseRenderer> CreateGLRenderer();