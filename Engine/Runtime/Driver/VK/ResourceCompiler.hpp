#pragma once

#include <vector>
#include <string>

namespace Eclipse {
	struct ShaderObject {
		std::vector<char> vertexSource;
		std::vector<char> fragmentSource;
	};
}

namespace EclipseResources {
	Eclipse::ShaderObject CreateShaderObject(std::string glsl_file_path);
};