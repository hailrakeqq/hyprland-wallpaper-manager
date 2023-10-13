#include "../include/utils.h"

std::string getFileName(std::string filePath) {
    std::filesystem::path path(filePath);
    return path.filename().string();
}

long getFileSize(std::string filePath){
    std::ifstream file(filePath, std::ios::binary);
    if(!file){
        std::cerr << "Can't open file." << std::endl;
        return 1;
    }

    file.seekg(0, std::ios::end);
    long fileSize = (long)file.tellg();
    file.close();
    return fileSize;
}

std::vector<image>::iterator getItemIndexInVector(std::vector<image> & vec, image *img){
    for (auto i = vec.begin(); i != vec.end(); ++i) {
        if (i->fullPath == img->fullPath) 
            return i;
    }
    return vec.end();
}
