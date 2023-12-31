#ifndef UTILS_H
#define UTILS_H

#include "../include/wallpaper.h"
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace utils {
    std::string getFileName(std::string filePath);
    std::string getPrimaryMonitorName();
    int getImageIntervalTimeInMinutes(std::string interval);
    long getFileSize(std::string filePath);
    std::vector<wallpaper>::iterator getItemIndexInVector(std::vector<wallpaper>& vec,
        wallpaper* img);

    wallpaper getRandomItem(const std::vector<wallpaper>& arr);
} // namespace utils
#endif // !UTILS_H