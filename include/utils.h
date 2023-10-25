#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>
#include <random>
#include <stdexcept>
#include "../include/imageManager.h"

namespace utils
{
    std::string getFileName(std::string filePath);
    int getImageIntervalTimeInMinutes(std::string interval);
    long getFileSize(std::string filePath);
    std::vector<image>::iterator getItemIndexInVector(std::vector<image> &vec, image *img);

    // template <typename T> 
    image getRandomItem(const std::vector<image> &arr);
}
#endif // !UTILS_H