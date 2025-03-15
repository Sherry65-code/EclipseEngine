# Basic setup
cmake_minimum_required(VERSION 3.10)
set(PROJECT_NAME "EclipseEngine")
project(${PROJECT_NAME})

# added subdirectories
add_subdirectory("ThirdParty/fmt")
add_subdirectory("ThirdParty/imgui")
add_subdirectory("ThirdParty/glfw")

# standard set
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# includes set
include_directories(".")
include_directories("ThirdParty/imgui/")
include_directories("ThirdParty/fmt/include/")
include_directories("ThirdParty/glfw/include/")
include_directories(${CMAKE_SOURCE_DIR}/Engine)

# source files
file(GLOB_RECURSE EngineCode "Engine/*.cpp" "Engine/*.hpp" "Engine/*.c")

# added compiler options
if (MSVC)
    add_compile_options("/utf-8")
endif()

# added executable
add_executable(${PROJECT_NAME} ${EngineCode})

# linked libraries
target_link_libraries(${PROJECT_NAME} imgui fmt::fmt glfw)