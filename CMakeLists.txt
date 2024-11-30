cmake_minimum_required(VERSION 3.10)

project(Eclipse)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(third_party/glfw)
add_subdirectory(third_party/fmt)

include_directories(core)
include_directories(third_party/glfw/include)
include_directories(third_party/fmt/include)

file(GLOB_RECURSE SOURCE_CORE "core/*.cpp" "core/*.hpp")

add_executable(EclipseDemo ${SOURCE_CORE})

target_link_libraries(EclipseDemo glfw fmt::fmt)