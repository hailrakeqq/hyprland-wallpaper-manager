#ifndef WALLPAPERCHANGER_H
#define WALLPAPERCHANGER_H
#include "../include/wallpaperManager.h"

class wallpaperChanger {
public:
    static bool setWallpaper(std::string monitors, wallpaper* img);
    static bool setWallpaper(std::string monitors, std::string wallpaperPath);
};
#endif // !WALLPAPERCHANGER_H
