#include "WindowManager.hpp"

#include <Engine/Standard/IO.hpp>

bool WindowManager::createNewWindow(WindowCreateInfo& window_create_info) {
    return true;
}

void WindowManager::update() {

}

bool WindowManager::shouldClose() {
    return false;
}

bool WindowManager::createGLContext() {
    return false;
}

void* WindowManager::win32_getWindowHandle() {
    // Returns nullptr because it is a windows function
    return nullptr;
}

WindowManager::~WindowManager() {

}