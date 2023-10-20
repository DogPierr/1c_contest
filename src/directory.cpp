#include "directory.h"

Directory::Directory(const std::string &path_to_dir) : _directory_path(path_to_dir), similarity_index(1) {
    for (const auto & entry : std::filesystem::directory_iterator(path_to_dir)) {
        _files_in_dir.emplace_back(entry.path());
    }
}

Directory::Directory(const std::string &path_to_dir, float similarity) : Directory(path_to_dir) {
    similarity_index = similarity;
}

const std::vector<File> &Directory::GetFiles() const {
    return _files_in_dir;
}

const std::string &Directory::GetPath() const {
    return _directory_path;
}

void Directory::CompareTo(const Directory &directory) const {
    std::vector<SimilarStrings> same_files;
    std::vector<SimilarStrings> similar_files;

    std::vector<std::string> not_in_dir_2;
    std::vector<std::string> not_in_dir_1;

    const auto& files_1 = GetFiles();
    const auto& files_2 = directory.GetFiles();

    std::vector<bool> is_file_2_similar_to_some_in_dir_1(files_2.size(), false);

    for (const auto& file_1 : files_1) {
        auto file_1_content = file_1.GetContent();
        size_t file_2_index = 0;
        bool is_file_1_in_dir_2 = false;
        for (const auto& file_2 : files_2) {
            auto result_of_comparation = file_2.CompareContentTo(file_1_content);
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

    WriteStatistics(same_files, similar_files, not_in_dir_2, is_file_2_similar_to_some_in_dir_1, files_2, directory);
}

void Directory::WriteStatistics(const std::vector<SimilarStrings> &same_files,
                                const std::vector<SimilarStrings> &similar_files,
                                const std::vector<std::string> &not_in_dir_2,
                                const std::vector<bool> &is_file_2_similar_to_some_in_dir_1,
                                const std::vector<File> &files_2,
                                const Directory& other_directory) const {
    std::cout << "Same files in both directories:\n";
    for (const auto& pair: same_files) {
        std::cout << pair.path_1 << " - " << pair.path_2 << '\n';
    }

    std::cout << "Similar files in both directories:\n";
    for (const auto& pair: similar_files) {
        std::cout << pair.path_1 << " - " << pair.path_2 << " - " << pair.similarity << '\n';
    }

    std::cout << "Files from directory " << GetPath() << " which are not present in " << other_directory.GetPath() << ":\n";
    for (const auto& file_path : not_in_dir_2) {
        std::cout << file_path << '\n';
    }

    std::cout << "Files from directory " << other_directory.GetPath() << " which are not present in " << GetPath() << ":\n";
    for (size_t i = 0; i < is_file_2_similar_to_some_in_dir_1.size(); ++i) {
        if (!is_file_2_similar_to_some_in_dir_1[i]) {
            std::cout << files_2[i].GetPath() << '\n';
        }
    }
}
