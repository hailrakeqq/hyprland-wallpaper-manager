#ifndef WALLPAPERCHANGER_H
#define WALLPAPERCHANGER_H
#include "../include/imageManager.h"

class wallpaperChanger {
public:
    static bool setWallpaper(std::string monitors, image* img);
    static bool setWallpaper(std::string monitors, std::string wallpaperPath);
};
#endif // !WALLPAPERCHANGER_H
