#include "ResourceCompiler.hpp"
#include <Runtime/Filesystem/FileSystem.hpp>
#include <iostream>
#include <sstream>
#include <optional>
#include <Runtime/Standard/IO.hpp>
static uint32_t shader_resource_counter = 0;

Eclipse::ShaderObject EclipseResources::CreateShaderObject(std::string glsl_file_path) {
    Eclipse::ShaderObject object;
    EclipseFileSystem::CreateDirectoryIfNotExists("EngineCache");
    EclipseFileSystem::CreateDirectoryIfNotExists("EngineCache/ShaderHistory");

    std::string vertexGlslFileName = glsl_file_path + ".vert";
    std::string fragmentGlslFileName = glsl_file_path + ".frag";
    std::string vertexSpirvFileName = "EngineCache/shader_resource_" + std::to_string(shader_resource_counter) + "v.spv";
    std::string fragmentSpirvFileName = "EngineCache/shader_resource_" + std::to_string(shader_resource_counter) + "f.spv";
    std::string vertexCacheFileName = "EngineCache/ShaderHistory/shader_resource_" + std::to_string(shader_resource_counter) + "v.bak";
    std::string fragmentCacheFileName = "EngineCache/ShaderHistory/shader_resource_" + std::to_string(shader_resource_counter) + "f.bak";

    if (EclipseFileSystem::Exists(vertexCacheFileName) || EclipseFileSystem::Exists(fragmentCacheFileName)) {
        std::string v_cache = EclipseFileSystem::ReadFileAsText(vertexCacheFileName);
        std::string v_current = EclipseFileSystem::ReadFileAsText(vertexGlslFileName);
        std::string f_cache = EclipseFileSystem::ReadFileAsText(fragmentCacheFileName);
        std::string f_current = EclipseFileSystem::ReadFileAsText(fragmentCacheFileName);
        if (v_cache == v_current && f_cache == f_current) {
            // Cache is not outdated
            object.vertexSource = EclipseFileSystem::ReadFileAsBinary(vertexSpirvFileName);
            object.fragmentSource = EclipseFileSystem::ReadFileAsBinary(fragmentSpirvFileName);
            io::print("Using Shader Cache for shader {}!", shader_resource_counter);
            return object;
        }
    }

    std::string vertexCommand = "glslc " + vertexGlslFileName + " -o " + vertexSpirvFileName;
    std::string fragmentCommand = "glslc " + fragmentGlslFileName + " -o " + fragmentSpirvFileName;

    int compileReturnCodeV = system(vertexCommand.c_str());
    int compileReturnCodeF = system(fragmentCommand.c_str());

    if (compileReturnCodeV != 0) {
        throw std::runtime_error("Failed to compile vertex shader: " + vertexGlslFileName);
    }
    if (compileReturnCodeF != 0) {
        throw std::runtime_error("Failed to compile fragment shader: " + fragmentGlslFileName);
    }

    object.vertexSource = EclipseFileSystem::ReadFileAsBinary(vertexSpirvFileName);
    object.fragmentSource = EclipseFileSystem::ReadFileAsBinary(fragmentSpirvFileName);

    EclipseFileSystem::CopyFileOverwrite(vertexGlslFileName, vertexCacheFileName);
    EclipseFileSystem::CopyFileOverwrite(fragmentGlslFileName, fragmentCacheFileName);

    shader_resource_counter++;
    return object;
}

