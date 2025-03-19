#pragma once

#include <fmt/core.h>
#include <fmt/color.h>
#include <mutex>

namespace io {

    enum class LogLevel {
        INFO,
        WARNING,
        ERROR,
        DEBUG
    };

    void log(LogLevel level, fmt::string_view format, fmt::format_args args);

    template <typename... Args>
    void logMessage(LogLevel level, fmt::format_string<Args...> format, Args&&... args) {
        log(level, format, fmt::make_format_args(std::forward<Args>(args)...));
    }

}