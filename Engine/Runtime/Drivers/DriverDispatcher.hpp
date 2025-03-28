#pragma once

#include <stdexcept>
#include "GL/GL.hpp"

namespace Eclipse {
    enum class DriverType {
        OpenGL, Vulkan
    };
} // namespace Eclipse

namespace DriverDispatcher {
    std::unique_ptr<Driver> DispatchDriver(Eclipse::DriverType type) {
        switch (type) {
            case Eclipse::DriverType::OpenGL:
                return std::make_unique<GL>();
            case Eclipse::DriverType::Vulkan:
                throw std::runtime_error("Vulkan Driver is under development!");
            default:
                throw std::runtime_error("Driver Not Found!");
        }
    }
};