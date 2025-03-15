#pragma once
#include <string>
#include <GLFW/glfw3.h>
#include <Engine/Standard/Types.hpp>

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
	b32 createNewWindow(WindowCreateInfo& window_create_info);
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
	* Set Mouse move callback function
	* @param MouseMoveCallbackFunction
	* @return void
	*/
	void setMouseMoveCallbackFunction(MouseMoveCallbackFunction mmcf);
	/**
	* Return window handle
	* @param none
	* @return struct GLFWwindow pointer
	*/
	GLFWwindow* getWindowHandle();

	~WindowManager();
};