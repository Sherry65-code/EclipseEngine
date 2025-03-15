#include "IO.hpp"

namespace io {
    std::mutex logMutex;

    void log(LogLevel level, fmt::string_view format, fmt::format_args args) {
        std::lock_guard<std::mutex> lock(logMutex);

        switch (level) {
        case LogLevel::INFO:
            fmt::vprint(format, args);
            fmt::print("\n");
            break;
        case LogLevel::WARNING:
            fmt::print(fmt::fg(fmt::color::yellow), "WARNING: ");
            fmt::vprint(format, args);
            fmt::print("\n");
            break;
        case LogLevel::ERROR:
            fmt::print(fmt::fg(fmt::color::red), "ERROR: ");
            fmt::vprint(format, args);
            fmt::print("\n");
            break;
        case LogLevel::DEBUG:
#ifndef NDEBUG
            fmt::print(fmt::fg(fmt::color::green_yellow), "DEBUG: ");
            fmt::vprint(format, args);
            fmt::print("\n");
#endif
            break;
        }
    }
}