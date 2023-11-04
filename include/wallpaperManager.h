#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include "configurator.h"
#include "utils.h"
#include "wallpaper.h"
#include <filesystem>
#include <iostream>
#include <vector>

namespace fs = std::filesystem;

class wallpaperManager {
public:
    std::string monitors;

    wallpaperManager(std::string imagesDirectoryPath);
    wallpaperManager(configurator* conf);

    int getImagesCount();
    std::vector<wallpaper> getImages();
    bool isImageExist(std::string imagePath);
    wallpaper* getImage(std::string imagePath);
    void addImage(wallpaper* img);
    void addImages(std::string imagesDirectoryPath);
    std::vector<wallpaper> getImages(std::string imagesDirectoryPath);
    void deleteImage(wallpaper* img);
    void deleteImage(int index);
    void clearImages();

private:
    configurator* conf;
    int wallpaperCount;
    std::string imagesDirectoryPath;
    std::vector<wallpaper> wallpapers;
    bool isValidImagesDirectory(std::string pathToDirectory);

    std::vector<wallpaper> getFilesInDirectory(std::string& directoryPath);
};
#endif // !IMAGEMANAGER_H