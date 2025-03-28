cmake_minimum_required(VERSION 3.10)

project(EclipseEngine)

add_subdirectory(Engine/External/fmt)
add_subdirectory(Engine/External/glfw)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("Engine")
include_directories("Engine/External/fmt/include")
include_directories("Engine/External/glfw/include")
include_directories("Engine/External/glad/include")

if (MSVC)
    add_compile_options(/utf-8)
    set_property(GLOBAL PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Engine")
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Engine/Demo")
endif()

file(GLOB_RECURSE RUNTIME_SOURCE "${CMAKE_SOURCE_DIR}/Engine/Runtime/*")
add_library(Runtime ${RUNTIME_SOURCE})

file(GLOB_RECURSE DEMO_SOURCE "${CMAKE_SOURCE_DIR}/Engine/Demo/*.cpp")
add_executable(EclipseEngineDemo ${DEMO_SOURCE})

target_link_libraries(EclipseEngineDemo Runtime fmt::fmt glfw)