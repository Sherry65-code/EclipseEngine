cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME "EclipseEngine")

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(".")

file(GLOB_RECURSE EngineCode "Engine/*")

add_executable(${PROJECT_NAME} ${EngineCode})