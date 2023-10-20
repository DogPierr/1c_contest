#include "comparator_of_directories.h"

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