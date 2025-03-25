#pragma once

#include <vector>
#include <string>

namespace Eclipse {
	struct File {
		std::string fullname;
		std::string firstname;
		std::string extension;
		bool isDirectory;
	};
};

namespace EclipseFileSystem {
	std::string ReadFileAsText(const std::string& file_name);
	std::vector<char> ReadFileAsBinary(const std::string& file_name);

	std::vector<Eclipse::File> ListDirectory(const std::string& directory_address);
	void CreateDirectoryIfNotExists(const std::string& directory_name);
};