#include "GL.hpp"

#include <Runtime/Standard/IO.hpp>

#include "External/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>


GLFWwindow* winptr{};

void GL::Initialize(void* winptr_vp) {
    // Assign Window pointer to global declrative variable
    winptr = (GLFWwindow*)winptr_vp;

    glfwMakeContextCurrent(winptr);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to load OpenGL!");
    }

}

void GL::UpdateFrame() {
    
}

GL::~GL() {

}