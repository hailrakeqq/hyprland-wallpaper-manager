#ifndef WALLPAPERMANAGER_H
#define WALLPAPERMANAGER_H

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

    wallpaperManager(std::string wallpapersDirectoryPath);
    wallpaperManager(configurator* conf);

    int getImagesCount();
    std::vector<wallpaper> getImages();
    bool isWallpaperExist(std::string wallpaperPath);
    wallpaper* getWallpaper(std::string wallpaperPath);
    void addWallpaper(wallpaper* img);
    void addWallpapers(std::string wallpapersDirectoryPath);
    void addWallpapers(std::vector<wallpaper> wallpapers);
    std::vector<wallpaper> getWallpapers(std::string wallpapersDirectoryPath);
    std::vector<wallpaper> getWallpapers();
    void deleteWallpaper(wallpaper* img);
    void deleteWallpaper(int index);
    void clearWallpapers();

private:
    configurator* conf;
    int wallpaperCount;
    std::string wallpapersDirectoryPath;
    std::vector<wallpaper> wallpapers;
    bool isValidWallpapersDirectory(std::string pathToDirectory);

    std::vector<wallpaper> getFilesInDirectory(std::string& directoryPath);
};
#endif // !WALLPAPERMANAGER_H