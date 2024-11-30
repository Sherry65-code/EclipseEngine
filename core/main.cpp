#include <window/window.hpp>

int main() {
	Window window = Window("Eclipse Engine Demo", 800, 500, false, false);
	Window::window_t window_instance = window.returnWindowInstance();

	while (!window.shouldWindowClose()) {
		glfwSwapBuffers(window_instance);
		glfwPollEvents();
	}
}