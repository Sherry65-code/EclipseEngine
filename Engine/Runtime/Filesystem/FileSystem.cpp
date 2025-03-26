#include "FileSystem.hpp"

#include <filesystem>
#include <fstream>
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include <External/stb_image.h>

namespace fs = std::filesystem;

std::string EclipseFileSystem::ReadFileAsText(const std::string& file_name) {
	std::ifstream file(file_name, std::ios::in | std::ios::ate);
	if (!file.is_open())
		throw std::runtime_error("Failed to open file!");

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
		throw std::runtime_error("Failed to open file!");

	size_t fileSize = static_cast<size_t>(file.tellg());
	std::vector<char> buffer(fileSize);

	file.seekg(0);
	file.read(buffer.data(), fileSize);
	file.close();

	return buffer;
}

Eclipse::RawImage EclipseFileSystem::LoadRawImageFromFile(const std::string& file_name) {
	Eclipse::RawImage image{};
	image.pixels = stbi_load(file_name.c_str(), &image.width, &image.height, nullptr, 4);
	return image;
}

void EclipseFileSystem::CreateDirectoryIfNotExists(const std::string& directory_name) {
	try { fs::create_directory(directory_name); }
	catch (const std::runtime_error& e) {};
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
	catch (const std::runtime_error& e) {
		throw std::runtime_error(e.what());
	}
	return files;
}

void EclipseFileSystem::CreateFileIfNotExists(const std::string& file_name) {
	if (!fs::exists(file_name)) {
		std::ofstream file(file_name);
		if (file); else throw std::runtime_error("Unable to create file!");
	}
}

bool EclipseFileSystem::Exists(const std::string& path) {
	return fs::exists(path);
}

void EclipseFileSystem::CopyFileOverwrite(const std::string & source, const std::string & dest) {
	fs::copy_file(source, dest, fs::copy_options::overwrite_existing);
}