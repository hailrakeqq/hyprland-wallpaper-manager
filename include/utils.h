#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>
#include "../include/imageManager.h"

std::string getFileName(std::string filePath);
long getFileSize(std::string filePath);
std::vector<image>::iterator getItemIndexInVector(std::vector<image> &vec, image *img);
