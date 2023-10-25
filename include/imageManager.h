#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <iostream>
#include <vector>
#include <filesystem>
#include "configurator.h"
#include "image.h"

namespace fs = std::filesystem;

class imageManager {
public:
    std::string monitors;
    
    imageManager(std::string imagesDirectoryPath);
    imageManager(configurator *conf);

    int getImagesCount();
    std::vector<image> getImages();
    bool isImageExist(std::string imagePath);
    image *getImage(std::string imagePath);
    void addImage(image *img);
    void addImages(std::string imagesDirectoryPath);
    std::vector<image> getImages(std::string imagesDirectoryPath);
    void deleteImage(image *img);
    void deleteImage(int index);
    void clearImages();

private:
    configurator *conf;
    int imageCount;
    std::string imagesDirectoryPath;
    std::vector<image> images;
    bool isValidImagesDirectory(std::string pathToDirectory);
    
    std::vector<image> getFilesInDirectory(std::string &directoryPath);
};
#endif // !IMAGEMANAGER_H