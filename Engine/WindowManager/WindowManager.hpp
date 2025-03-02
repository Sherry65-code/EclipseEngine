#pragma once
#include <string>

class WindowManager {
public:

	typedef void (*MouseMoveCallbackFunction)(bool*, int x, int y);

	struct WindowCreateInfo {
		std::string title;
		int width;
		int height;
		bool resizable;
		bool fullscreen;
	};

	/**
	* Creates new window
	* @param window_create_info Takes window creation struct
	* @return Was window creation successfull
	*/
	bool createNewWindow(WindowCreateInfo& window_create_info);
	/**
	* Updates window to show changes
	* @param none
	* @return void
	*/
	void update();
	/**
	* Should window close
	* @param none
	* @return should window close
	*/
	bool shouldClose();
	/**
	* Creates OpenGL Context
	* @param none
	* @return is opengl context creation successfull
	*/
	bool createGLContext();
	/**
	* Returns Window Handle
	* @param none
	* @return void pointer window handle (Returns nullptr on linux)
	*/
	void* win32_getWindowHandle();
	/**
	* Set Mouse move callback function
	* @param MouseMoveCallbackFunction
	* @return void
	*/
	void setMouseMoveCallbackFunction(MouseMoveCallbackFunction mmcf);

	~WindowManager();
};