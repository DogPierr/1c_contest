#pragma once
#include "directory.h"

struct SimilarStrings {
    SimilarStrings(const std::string& path_1, const std::string& path_2, float similarity) : path_1(path_1), path_2(path_2), similarity(similarity) {}
    std::string path_1;
    std::string path_2;
    float similarity;
};

void ComparatorOfDirectories(const Directory& directory_1, const Directory& directory_2, float similarity_index);
