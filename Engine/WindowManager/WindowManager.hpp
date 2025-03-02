#pragma once
#include <string>

class WindowManager {
public:
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

	~WindowManager();
};