#pragma once

#include <vector>
#include <string>

namespace Eclipse {
	struct RawImage {
		int width;
		int height;
		unsigned char* pixels;
	};
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
	Eclipse::RawImage LoadRawImageFromFile(const std::string& file_name);

	std::vector<Eclipse::File> ListDirectory(const std::string& directory_address);
	void CreateDirectoryIfNotExists(const std::string& directory_name);
	void CreateFileIfNotExists(const std::string& file_name);
	bool Exists(const std::string& path);
	void CopyFileOverwrite(const std::string& source, const std::string& dest);
};