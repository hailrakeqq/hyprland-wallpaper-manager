#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include "settings_ui.h"
#include "utils.h"
#include "wallpaper.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

class settings_ui; // forward declaration

using json = nlohmann::json;
namespace fs = std::filesystem;

enum imageType {
    WALLPAPER_MANAGER,
    PLAYLIST
};

class configurator {
public:
    configurator(std::string configFilePath);

    std::vector<wallpaper> getWallpapersFromConfig();
    void addWallpaper(wallpaper* img, imageType type);
    void addWallpapers(std::vector<wallpaper> wallpapers, imageType type);
    void removeWallpaper(wallpaper* img, imageType type);
    void removeWallpaper(uint index, imageType type);
    void setImageSchedulerType(bool type);
    void updateScheduler(json& scheduler);
    void updateMonitors(std::string monitors);
    json getConfig();
    std::string getMonitors();
    void saveConfig();

private:
    bool isImageExistInConfig(wallpaper* img);
    json createJsonWallpaper(wallpaper* img);
    std::string configPath;
    json config;
};

#endif // CONFIGURATOR_H