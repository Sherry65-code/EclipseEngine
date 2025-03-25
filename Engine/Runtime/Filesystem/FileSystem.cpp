#include "FileSystem.hpp"

#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

std::string EclipseFileSystem::ReadFileAsText(const std::string& file_name) {
	std::ifstream file(file_name, std::ios::in | std::ios::ate);
	if (!file.is_open())
		throw std::exception("Failed to open file!");

	size_t fileSize = static_cast<size_t>(file.tellg());
	std::string content(fileSize, '\0');

	file.seekg(0);
	file.read(content.data(), fileSize);
	file.close();

	return content;
}

std::vector<char> EclipseFileSystem::ReadFileAsBinary(const std::string& file_name) {
	std::ifstream file(file_name, std::ios::binary | std::ios::ate);
	if (!file.is_open())
		throw std::exception("Failed to open file!");

	size_t fileSize = static_cast<size_t>(file.tellg());
	std::vector<char> buffer(fileSize);

	file.seekg(0);
	file.read(buffer.data(), fileSize);
	file.close();

	return buffer;
}

void EclipseFileSystem::CreateDirectoryIfNotExists(const std::string& directory_name) {
	try { fs::create_directory(directory_name); }
	catch (const std::exception& e) {};
}

std::vector<Eclipse::File> EclipseFileSystem::ListDirectory(const std::string& directory_address) {
	std::vector<Eclipse::File> files{};
	try {
		for (const auto& entry : fs::directory_iterator(directory_address)) {
			Eclipse::File file{};
			file.fullname = entry.path().string();
			file.firstname = entry.path().stem().string();
			file.isDirectory = entry.is_directory();
			file.extension = entry.path().extension().string();
			files.push_back(file);
		}
	}
	catch (const std::exception& e) {
		throw std::exception(e.what());
	}
	return files;
}