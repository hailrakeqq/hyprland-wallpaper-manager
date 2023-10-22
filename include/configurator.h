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

class configurator {
public:
    configurator(std::string configFilePath);
    std::vector<image> getImagesFromConfig();
    void addImageToConfig(image *img);
    void removeImageFromConfig(image *img);
    void updateScheduler(json &scheduler);
    json getConfig();
    void saveConfig();

private:
    bool isImageExistInConfig(image *img);
    std::string configPath;
    json config;
};

#endif // CONFIGURATOR_H