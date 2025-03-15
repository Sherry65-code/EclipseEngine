cmake_minimum_required(VERSION 3.10)

project("imgui")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(".")
include_directories("../glfw/include/")

file(GLOB_RECURSE IMGUICode "*")

add_library(imgui ${IMGUICode})