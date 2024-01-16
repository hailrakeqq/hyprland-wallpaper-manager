#ifndef UTILS_H
#define UTILS_H

#include "wallpaper.h"
#include <algorithm>
#include <chrono>
#include <cstring>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <stdexcept>
#include <time.h>
#include <vector>

namespace utils {
    std::string getFileName(std::string filePath);
    time_t getLastModifiedTime(std::string filePath);
    std::string getPrimaryMonitorName();
    int getImageIntervalTimeInMinutes(std::string interval);
    long getFileSize(std::string filePath);
    std::vector<wallpaper>::iterator getItemIndexInVector(std::vector<wallpaper>& vec, wallpaper* img);
    wallpaper getRandomItem(const std::vector<wallpaper>& arr);

    template <typename T>
    bool compareAscending(T a, T b);

    template <typename T>
    bool compareDescending(T a, T b);

    void sortByPropertyAscending(std::vector<wallpaper> wallpapers);

    void sortByPropertyDescending(std::vector<wallpaper> wallpapers);

} // namespace utils
#endif // !UTILS_H