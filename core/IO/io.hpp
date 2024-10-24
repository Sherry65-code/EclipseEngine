/*
    IO Library for high performance modern formatted output to console.
    Also stores debug info and only displays when debug mode is on.
    Supports coloured output for different level error or warning messages.
*/

#pragma once

#include <fmt/core.h>
#include <fmt/color.h>

namespace io {

#ifdef NDEBUG
    constexpr bool debug = false;
#else
    constexpr bool debug = true;
#endif

    template<typename... Args>
    void printInline(fmt::format_string<Args...> format, Args&&... args) {
        fmt::print(format, args...);
    }

    template<typename... Args>
    void print(fmt::format_string<Args...> format, Args&&... args) {
        fmt::println(format, args...);
    }

    template<typename... Args>
    void printError(fmt::format_string<Args...> format, Args&&... args) {
        fmt::print(fmt::fg(fmt::color::red), "ERROR: ");
        fmt::println(format, args...);
    }

    template<typename... Args>
    void printErrorAndExit(fmt::format_string<Args...> format, Args&&... args) {
        fmt::print(fmt::fg(fmt::color::red), "ERROR: ");
        fmt::println(format, args...);
        exit(EXIT_FAILURE);
    }
    
    template<typename... Args>
    void printWarning(fmt::format_string<Args...> format, Args&&... args) {
        fmt::print(fmt::fg(fmt::color::yellow), "WARNING: ");
        fmt::println(format, args...);
    }

    template<typename... Args>
    void printDebug(fmt::format_string<Args...> format, Args&&... args) {
        if (!debug) return;
        fmt::print(fmt::fg(fmt::color::green_yellow), "DEBUG: ");
        fmt::println(format, args...);
    }
};