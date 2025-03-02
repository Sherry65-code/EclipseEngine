#pragma once
#include <string>
#include <vector>

namespace efs {

    // File Operations

    /**
     * Checks if a file exists.
     * @param path The path to the file.
     * @return True if the file exists, otherwise false.
     */
    bool fileExists(const std::string& path);

    /**
     * Reads the entire file as a string.
     * @param path The path to the file.
     * @return The contents of the file as a string.
     */
    std::string readFileAsString(const std::string& path);

    /**
     * Reads a file as a binary buffer.
     * @param path The path to the file.
     * @return A vector of bytes representing the file's contents.
     */
    std::vector<char> readFileAsBinary(const std::string& path);

    /**
     * Writes data to a file, overwriting if it exists.
     * @param path The path to the file.
     * @param data The data to write.
     * @return True if successful, otherwise false.
     */
    bool writeFile(const std::string& path, const std::string& data);

    /**
     * Appends data to an existing file.
     * @param path The path to the file.
     * @param data The data to append.
     * @return True if successful, otherwise false.
     */
    bool appendToFile(const std::string& path, const std::string& data);

    /**
     * Deletes a file.
     * @param path The path to the file.
     * @return True if successful, otherwise false.
     */
    bool deleteFile(const std::string& path);

    // Directory Operations

    /**
     * Checks if a directory exists.
     * @param path The path to the directory.
     * @return True if the directory exists, otherwise false.
     */
    bool directoryExists(const std::string& path);

    /**
     * Creates a directory.
     * @param path The path to the directory.
     * @return True if successful, otherwise false.
     */
    bool createDirectory(const std::string& path);

    /**
     * Deletes a directory.
     * @param path The path to the directory.
     * @return True if successful, otherwise false.
     */
    bool deleteDirectory(const std::string& path);

    /**
     * Lists all files in a directory.
     * @param path The path to the directory.
     * @param recursive If true, includes files from subdirectories.
     * @return A vector of file paths.
     */
    std::vector<std::string> listFilesInDirectory(const std::string& path, bool recursive = false);

    // Path Handling

    /**
     * Gets the file extension from a given path.
     * @param path The file path.
     * @return The file extension (including the dot), or an empty string if none.
     */
    std::string getFileExtension(const std::string& path);

    /**
     * Gets the file name from a given path.
     * @param path The file path.
     * @param includeExtension Whether to include the file extension.
     * @return The file name.
     */
    std::string getFileName(const std::string& path, bool includeExtension = true);

    /**
     * Gets the parent directory of a given path.
     * @param path The file or directory path.
     * @return The parent directory path.
     */
    std::string getParentDirectory(const std::string& path);

    /**
     * Joins two paths into a single valid path.
     * @param path1 The first path.
     * @param path2 The second path.
     * @return The combined path.
     */
    std::string joinPaths(const std::string& path1, const std::string& path2);

    /**
     * Normalizes a file path (e.g., removes redundant separators).
     * @param path The file path.
     * @return The normalized file path.
     */
    std::string normalizePath(const std::string& path);

    // Asset Management

    /**
     * Gets the absolute path from a relative path.
     * @param relativePath The relative file path.
     * @return The absolute file path.
     */
    std::string getAbsolutePath(const std::string& relativePath);

    /**
     * Copies a file from one location to another.
     * @param source The source file path.
     * @param destination The destination file path.
     * @return True if successful, otherwise false.
     */
    bool copyFile(const std::string& source, const std::string& destination);

}