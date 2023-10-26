#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include <string>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <filesystem>
#include "image.h"

using json = nlohmann::json;
namespace fs = std::filesystem;

enum imageType
{
    IMAGE_MANAGER,
    PLAYLIST
};

class configurator
{
public:
    configurator(std::string configFilePath);
    std::vector<image> getImagesFromConfig();
    void addImage(image *img, imageType type);
    void removeImage(image *img, imageType type);
    void removeImage(uint index, imageType type);
    void setImageSchedulerType(bool type);
    void updateScheduler(json &scheduler);
    void updateMonitors(std::string monitors);
    json getConfig();
    std::string getMonitors();
    void saveConfig();

private:
    bool isImageExistInConfig(image *img);
    json createJsonImage(image *img);
    std::string configPath;
    json config;
};

#endif // CONFIGURATOR_H