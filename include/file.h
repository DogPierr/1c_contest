#pragma once
#include <iostream>
#include <vector>

class File {
public:
    File() = default;

    File(const std::string& path_to_file);

    float CompareTo(const File& file) const;

    const std::string& GetContent() const;

    const std::string & GetPath() const;

private:
    std::string _file_path;
    std::string _file_content;

    std::string GetContentOfFile(const std::string& path);
};