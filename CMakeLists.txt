cmake_minimum_required(VERSION 3.5)

project(EclipseEngine)

set(BUILD_SHARED_LIBS OFF)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Vulkan REQUIRED)

include_directories(third_party)
include_directories(third_party/glfw/include)
include_directories(third_party/fmt/include)
include_directories(core/)
include_directories(engine/)
include_directories(editor/)
include_directories(${VULKAN_INCLUDE_DIR})

add_subdirectory(third_party/glfw)
add_subdirectory(third_party/fmt)

link_libraries(Vulkan::Vulkan)
link_libraries(fmt::fmt)
link_libraries(glfw)

file(GLOB_RECURSE CORE_SRC core/*)
file(GLOB_RECURSE ENGINE_SRC engine/*)
file(GLOB_RECURSE EDITOR_SRC editor/*)

add_library(EclipseEngine ${ENGINE_SRC})

add_library(Core ${CORE_SRC})

add_executable(MoonEditor ${EDITOR_SRC})

target_link_libraries(MoonEditor EclipseEngine fmt::fmt)

# file(GLOB_RECURSE SHADERS_FILES shaders/*)

# add_custom_target(Shaders SOURCES ${SHADERS_FILES})

# foreach(Shader ${SHADERS_FILES})
#     get_filename_component(Shader_name ${Shader} NAME_WE)
#     add_custom_command(
#         TARGET Shaders
#         PRE_BUILD
#         COMMAND ${Vulkan_INCLUDE_DIRS}/../bin/glslc ${Shader} -o ${CMAKE_BINARY_DIR}/${Shader_name}.spv
#         COMMENT "Compiling shader ${Shader_name}"
#     )
# endforeach()

# file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
