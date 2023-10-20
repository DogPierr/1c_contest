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
    Directory(const std::string& path_to_dir, float similarity);

    const std::vector<File>& GetFiles() const;

    const std::string& GetPath() const;

    void CompareTo(const Directory& directory) const;

private:
    struct SimilarStrings {
        SimilarStrings(const std::string& path_1, const std::string& path_2, float similarity) : path_1(path_1), path_2(path_2), similarity(similarity) {}
        std::string path_1;
        std::string path_2;
        float similarity;
    };

    void WriteStatistics(const std::vector<SimilarStrings>& same_files,
                         const std::vector<SimilarStrings>& similar_files,
                         const std::vector<std::string>& not_in_dir_2,
                         const std::vector<bool>& is_file_2_similar_to_some_in_dir_1,
                         const std::vector<File>& files_2,
                         const Directory& other_directory) const;

    std::string _directory_path;
    std::vector<File> _files_in_dir;
    float similarity_index = 1;
};

