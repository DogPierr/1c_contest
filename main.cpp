#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <fstream>
#include <algorithm>

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

struct SimilarStrings {
    SimilarStrings(const std::string& path_1, const std::string& path_2, float similarity) : path_1(path_1), path_2(path_2), similarity(similarity) {}
    std::string path_1;
    std::string path_2;
    float similarity;
};

void ComparatorOfDirectories(const Directory& directory_1, const Directory& directory_2, float similarity_index) {
    std::vector<SimilarStrings> same_files;
    std::vector<SimilarStrings> similar_files;

    std::vector<std::string> not_in_dir_2;
    std::vector<std::string> not_in_dir_1;

    const auto& files_1 = directory_1.GetFiles();
    const auto& files_2 = directory_2.GetFiles();

    std::vector<bool> is_file_2_similar_to_some_in_dir_1(directory_2.GetFiles().size(), false);

    for (const auto& file_1 : files_1) {
        size_t file_2_index = 0;
        bool is_file_1_in_dir_2 = false;
        for (const auto& file_2 : files_2) {
            auto result_of_comparation = file_1.CompareTo(file_2);
            if (result_of_comparation == 1) {
                is_file_1_in_dir_2 = true;
                is_file_2_similar_to_some_in_dir_1[file_2_index] = true;
                same_files.emplace_back(file_1.GetPath(), file_2.GetPath(), result_of_comparation);
            } else if (result_of_comparation >= similarity_index) {
                is_file_1_in_dir_2 = true;
                is_file_2_similar_to_some_in_dir_1[file_2_index] = true;
                similar_files.emplace_back(file_1.GetPath(), file_2.GetPath(), result_of_comparation);
            }
            ++file_2_index;
        }
        if (!is_file_1_in_dir_2) {
            not_in_dir_2.push_back(file_1.GetPath());
        }
    }

    std::cout << "Same files in both directories:\n";
    for (const auto& pair: same_files) {
        std::cout << pair.path_1 << " - " << pair.path_2 << '\n';
    }

    std::cout << "Similar files in both directories:\n";
    for (const auto& pair: similar_files) {
        std::cout << pair.path_1 << " - " << pair.path_2 << " - " << pair.similarity << '\n';
    }

    std::cout << "Files from directory " << directory_1.GetPath() << " which are not present in " << directory_2.GetPath() << ":\n";
    for (const auto& file_path : not_in_dir_2) {
        std::cout << file_path << '\n';
    }

    std::cout << "Files from directory " << directory_2.GetPath() << " which are not present in " << directory_1.GetPath() << ":\n";
    for (size_t i = 0; i < is_file_2_similar_to_some_in_dir_1.size(); ++i) {
        if (!is_file_2_similar_to_some_in_dir_1[i]) {
            std::cout << files_2[i].GetPath() << '\n';
        }
    }

}


int main(int argc, char *argv[]) {
//    if (argc != 4) {
//        return 1;
//    }

//    Directory directory_1(argv[1]);
//    Directory directory_2(argv[2]);
//    float similarity_index = std::stof(argv[3]);

    Directory directory_1("dir_1");
    Directory directory_2("dir_2");
    float similarity_index = std::stof("0.5");

    ComparatorOfDirectories(directory_1, directory_2, similarity_index);
}
