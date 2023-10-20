#include "file.h"
#include <algorithm>
#include <fstream>

float File::CompareContentTo(const std::string &string_2) const {
    std::string string_1 = GetContent();

    size_t size_of_string_1 = string_1.size();
    size_t size_of_string_2 = string_2.size();

    std::vector<std::vector<size_t>> dp(size_of_string_1 + 1, std::vector<size_t>(size_of_string_2 + 1));

    for (size_t row = 0; row <= size_of_string_1; ++row) {
        for (size_t column = 0; column <= size_of_string_2; ++column) {
            if (row == 0) {
                dp[row][column] = column;
            } else if (column == 0) {
                dp[row][column] = row;
            } else if (string_1[row - 1] == string_2[column - 1]) {
                dp[row][column] = dp[row - 1][column - 1];
            } else {
                dp[row][column] = 1 + std::min({dp[row - 1][column], dp[row][column - 1], dp[row - 1][column - 1]});
            }
        }
    }

    size_t dist = dp[size_of_string_1][size_of_string_2];
    size_t maxLength = std::max(string_1.size(), string_2.size());
    float similarity = 1 - (static_cast<float>(dist) / static_cast<float>(maxLength));

    return similarity;
}

File::File(const std::string &path_to_file) : _file_path(path_to_file), _file_content(GetContentOfFile(path_to_file)) {}

std::string File::GetContent() const {
    return GetContentOfFile(_file_path);
}

const std::string &File::GetPath() const {
    return _file_path;
}

std::string File::GetContentOfFile(const std::string &path) const {
    std::ifstream file(path);
    std::string result;
    std::string line;

    while (std::getline(file, line)) {
        result += line;
    }

    file.close();

    return result;
}
