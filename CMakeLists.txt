cmake_minimum_required(VERSION 3.10)

project(EclipseEngine)

add_subdirectory(Engine/External/fmt)
add_subdirectory(Engine/External/glfw)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Vulkan REQUIRED)

include_directories("Engine")
include_directories("Engine/External/fmt/include")
include_directories("Engine/External/glfw/include")
include_directories("Engine/External/volk")
include_directories("Engine/External/")
include_directories("Engine/External/VulkanMemoryAllocator/include")
include_directories(${Vulkan_INCLUDE_DIRS})

file(GLOB_RECURSE RUNTIME_SOURCES "Engine/Runtime/*.cpp" "Engine/Runtime/*.hpp" "Engine/Runtime/*.c" "Engine/Runtime/*.h")
# file(GLOB_RECURSE EDITOR_SOURCES "Editor/*.cpp" "Editor/*.hpp" "Editor/*.c" "Editor/*.h")
file(GLOB_RECURSE GAME_SOURCES "Engine/Game/*.cpp" "Engine/Game/*.hpp" "Engine/Game/*.c" "Engine/Game/*.h")
file(GLOB VOLK_SOURCES "Engine/External/volk/*.c" "Engine/External/volk/*.h")

if (MSVC)
    add_compile_options(/utf-8)
    set_property(GLOBAL PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Engine")
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Engine")
endif()

add_library(Runtime ${RUNTIME_SOURCES})
add_library(Volk ${VOLK_SOURCES})
add_executable(EclipseEngineDemo ${GAME_SOURCES})

target_link_libraries(EclipseEngineDemo Runtime Volk fmt::fmt glfw)