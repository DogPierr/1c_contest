#include "file.h"
#include <algorithm>
#include <fstream>

float File::CompareTo(const File &file) const{
    std::string string_1 = GetContent();
    std::string string_2 = file.GetContent();

    size_t size_of_string_1 = string_1.size();
    size_t size_of_string_2 = string_2.size();

    size_t dp[size_of_string_1 + 1][size_of_string_2 + 1];

    for (size_t i = 0; i <= size_of_string_1; ++i) {
        for (size_t j = 0; j <= size_of_string_2; ++j) {
            if (i == 0) {
                dp[i][j] = j;
            } else if (j == 0) {
                dp[i][j] = i;
            } else if (string_1[i - 1] == string_2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + std::min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
            }
        }
    }

    size_t dist = dp[size_of_string_1][size_of_string_2];
    size_t maxLength = std::max(_file_content.length(), file.GetContent().length());
    float similarity = 1 - (static_cast<float>(dist) / static_cast<float>(maxLength));

    return similarity;
}

File::File(const std::string &path_to_file) : _file_path(path_to_file), _file_content(GetContentOfFile(path_to_file)) {}

const std::string &File::GetContent() const {
    return _file_content;
}

std::string File::GetContentOfFile(const std::string &path) {
    std::ifstream file(path);
    std::string result;
    std::string line;

    while(std::getline(file, line)) {
        result += line;
    }

    file.close();

    return result;
}

const std::string & File::GetPath() const {
    return _file_path;
}
