#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include "file.h"

class Directory {
public:
    Directory() = default;

    Directory(const std::string& path_to_dir);

    const std::vector<File>& GetFiles() const;

    const std::string& GetPath() const;

    void CompareTo(const Directory& directory);

private:
    std::string _directory_path;
    std::vector<File> _files_in_dir;
};

