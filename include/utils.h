#ifndef UTILS_H
#define UTILS_H

#include "../include/imageManager.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace utils {
    std::string getFileName(std::string filePath);
    int getImageIntervalTimeInMinutes(std::string interval);
    long getFileSize(std::string filePath);
    std::vector<image>::iterator getItemIndexInVector(std::vector<image>& vec,
        image* img);

    // template <typename T>
    image getRandomItem(const std::vector<image>& arr);
} // namespace utils
#endif // !UTILS_H