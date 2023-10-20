#include "directory.h"

Directory::Directory(const std::string &path_to_dir) : _directory_path(path_to_dir) {
    for (const auto & entry : std::filesystem::directory_iterator(path_to_dir)) {
        _files_in_dir.emplace_back(entry.path());
    }
}

const std::vector<File> &Directory::GetFiles() const {
    return _files_in_dir;
}

const std::string &Directory::GetPath() const {
    return _directory_path;
}