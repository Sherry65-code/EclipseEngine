#include "FS.hpp"
#include <filesystem>
#include <iostream>
#include <fstream>

namespace fs = std::filesystem;

namespace efs {

    // File Operations
    bool fileExists(const std::string& path) {
        return fs::exists(path);
    }

    std::string readFileAsString(const std::string& path) { 
        if (!fileExists(path)) return "";
        std::string line;
        std::string wf;
        std::ifstream f(path);
        while (std::getline(f, line)) {
            wf += line + "\n";
        }
        f.close();
        return wf;
    }
    
    std::vector<char> readFileAsBinary(const std::string& path) {
        if (!fileExists(path)) return {};
        std::vector<char> file_content;
        uintmax_t file_size = fs::file_size(path);
        file_content.resize(file_size);
        std::ifstream f(path, std::ios::binary | std::ios::in);
        f.read(file_content.data(), file_size);
        f.close();
        return file_content;
    }

    bool writeFile(const std::string& path, const std::string& data) { 
        return false; 
    }

    bool appendToFile(const std::string& path, const std::string& data) { 
        return false; 
    }

    bool deleteFile(const std::string& path) { 
        return false; 
    }

    // Directory Operations
    bool directoryExists(const std::string& path) { 
        return false; 
    }

    bool createDirectory(const std::string& path) { 
        return false; 
    }

    bool deleteDirectory(const std::string& path) { 
        return false; 
    }

    std::vector<std::string> listFilesInDirectory(const std::string& path, bool recursive) { 
        return {}; 
    }


    // Path Handling
    std::string getFileExtension(const std::string& path) { 
        return ""; 
    }

    std::string getFileName(const std::string& path, bool includeExtension) { 
        return ""; 
    }

    std::string getParentDirectory(const std::string& path) {
        return ""; 
    }

    std::string joinPaths(const std::string& path1, const std::string& path2) { 
        return ""; 
    }

    std::string normalizePath(const std::string& path) { 
        return ""; 
    }

    // Asset Management
    std::string getAbsolutePath(const std::string& relativePath) { 
        return ""; 
    }

    bool copyFile(const std::string& source, const std::string& destination) { 
        return false; 
    }

}
