#include "directory.h"
#include "comparator_of_directories.h"

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