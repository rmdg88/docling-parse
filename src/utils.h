//-*-C++-*-

#ifndef RESOURCE_UTILS_H_
#define RESOURCE_UTILS_H_

#include <iostream>
#include <filesystem>
#include <string>

// Platform-specific includes
#ifdef _WIN32
#include <sys/stat.h>
#define lstat _stat
#else
#include <sys/stat.h>
#include <unistd.h>
#endif

class resource_utils
{
public:

    // Constants for package name and resources path
    const static inline std::filesystem::path package_name = "docling_parse";
    const static inline std::filesystem::path resources_relative_path = "pdf_resources";

public:

    // Function to set the resources directory
    static bool set_resources_dir(std::filesystem::path path);

    // Function to get the resources directory
    static std::filesystem::path get_resources_dir(bool verify = true);

private:

    // Platform-independent ROOT_PATH initialization
    static inline std::filesystem::path ROOT_DIR = ROOT_PATH; // ROOT_PATH is defined during compilation
    static inline std::filesystem::path PACKAGE_DIR = ROOT_PATH / package_name;
    static inline std::filesystem::path RESOURCES_DIR = PACKAGE_DIR / resources_relative_path;

    // Helper function to check if a path is a directory
    static bool is_directory(const std::filesystem::path& path);
};

// Implementation of set_resources_dir
bool resource_utils::set_resources_dir(std::filesystem::path path)
{
    RESOURCES_DIR = path;

    if (std::filesystem::exists(RESOURCES_DIR))
    {
        PACKAGE_DIR = RESOURCES_DIR.parent_path();
        ROOT_DIR = PACKAGE_DIR.parent_path();

        return true;
    }
    else
    {
        return false;
    }
}

// Implementation of get_resources_dir
std::filesystem::path resource_utils::get_resources_dir(bool verify)
{
    if (verify && !std::filesystem::exists(RESOURCES_DIR))
    {
        std::cout << __FILE__ << ":" << __LINE__ << "\t"
                  << "resources-dir does not exist ..." << "\n";
    }

    return RESOURCES_DIR;
}

// Platform-specific directory check
bool resource_utils::is_directory(const std::filesystem::path& path)
{
#ifdef _WIN32
    struct _stat st;
    return (lstat(path.c_str(), &st) == 0 && (st.st_mode & _S_IFDIR));
#else
    struct stat st;
    return (lstat(path.c_str(), &st) == 0 && (st.st_mode & S_IFDIR));
#endif
}

#endif
