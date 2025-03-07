cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME "EclipseEngine")

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(".")
include_directories("ThirdParty/imgui/")
include_directories(${CMAKE_SOURCE_DIR}/Engine)

file(GLOB_RECURSE EngineCode "Engine/*.cpp" "Engine/*.hpp" "Engine/*.c")
file(GLOB_RECURSE IMGUICode "ThirdParty/imgui/*")

if (MSVC)
    add_compile_options("/utf-8")
endif()

add_library(imgui ${IMGUICode})

add_executable(${PROJECT_NAME} ${EngineCode})

target_link_libraries(${PROJECT_NAME} PUBLIC imgui)
