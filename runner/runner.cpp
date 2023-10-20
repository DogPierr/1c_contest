#include "directory.h"

int main(int argc, char *argv[]) {
//    if (argc != 4) {
//        return 1;
//    }

//    float similarity_index = std::stof(argv[3]);
//    Directory directory_1(argv[1], similarity_index);
//    Directory directory_2(argv[2], similarity_index);

    float similarity_index = std::stof("0.5");
    Directory directory_1("dir_1", similarity_index);
    Directory directory_2("dir_2", similarity_index);

    directory_1.CompareTo(directory_2);
}