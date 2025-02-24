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

	bool createNewWindow(WindowCreateInfo& window_create_info);
	void update();
	bool shouldClose();

	~WindowManager();
};