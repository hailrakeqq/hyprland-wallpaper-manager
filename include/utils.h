#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>
#include "../include/imageManager.h"
namespace utils
{
    std::string getFileName(std::string filePath);
    int getImageIntervalTimeInMinutes(std::string interval);
    long getFileSize(std::string filePath);
    image *getRandomImage(std::vector<image> &images);
    std::vector<image>::iterator getItemIndexInVector(std::vector<image> &vec, image *img);
}