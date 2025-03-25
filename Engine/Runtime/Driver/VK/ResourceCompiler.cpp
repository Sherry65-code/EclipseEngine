#include "ResourceCompiler.hpp"
#include <Runtime/Filesystem/FileSystem.hpp>
#include <iostream>
#include <sstream>

static uint32_t shader_resource_counter = 0;

Eclipse::ShaderObject EclipseResources::CreateShaderObject(std::string glsl_file_path) {
    Eclipse::ShaderObject object;
    EclipseFileSystem::CreateDirectoryIfNotExists("EngineCache");

    std::stringstream vertexCommand, fragmentCommand;
    vertexCommand << "glslc " << glsl_file_path << ".vert -o EngineCache/shader_resource_" << shader_resource_counter << "v.spv";
    fragmentCommand << "glslc " << glsl_file_path << ".frag -o EngineCache/shader_resource_" << shader_resource_counter << "f.spv";

    int compileReturnCodeV = system(vertexCommand.str().c_str());
    int compileReturnCodeF = system(fragmentCommand.str().c_str());

    if (compileReturnCodeV != 0) {
        throw std::exception("glsl2spirv_err_vertex");
    }
    if (compileReturnCodeF != 0) {
        throw std::exception("glsl2spirv_err_fragment");
    }

    std::string engineCacheNameV = "EngineCache/shader_resource_" + std::to_string(shader_resource_counter) + "v.spv";
    std::string engineCacheNameF = "EngineCache/shader_resource_" + std::to_string(shader_resource_counter) + "f.spv";

    object.vertexSource = EclipseFileSystem::ReadFileAsBinary(engineCacheNameV);
    object.fragmentSource = EclipseFileSystem::ReadFileAsBinary(engineCacheNameF);

    shader_resource_counter++;
    return object;
}
