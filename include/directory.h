#pragma once


class Directory {
public:
    Directory() = default;

    Directory(const std::string& path_to_dir);

    const std::vector<File>& GetFiles();

    void CompareTo(const Directory& directory);

private:
    std::string _directory_path;
    std::vector<File> _files_in_dir;
};
