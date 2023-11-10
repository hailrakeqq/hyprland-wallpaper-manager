#include "../include/configurator.h"

configurator::configurator(std::string configFilePath) {
    configPath = configFilePath;
    if (fs::is_regular_file(configFilePath)) {
        std::ifstream fileStream(configFilePath);
        fileStream >> config;
        fileStream.close();
        return;
    }

    std::string monitorInput = utils::getPrimaryMonitorName();
    if (!monitorInput.empty())
        config["monitors"] = monitorInput;
    else {
        config["monitors"] = "";
    }

    config["images"] = json::array();
    config["scheduler"] = json::object();
    saveConfig();
}

std::vector<wallpaper> configurator::getWallpapersFromConfig() {
    std::vector<wallpaper> images;

    for (auto jsonImage : configurator::config["images"]) {
        wallpaper img;
        img.fullPath = jsonImage["fullPath"];
        img.name = jsonImage["name"];
        img.size = jsonImage["size"];

        images.push_back(img);
    }

    return images;
}

void configurator::updateScheduler(json& scheduler) {
    config["scheduler"] = scheduler;
    saveConfig();
}

void configurator::updateMonitors(std::string monitors) {
    config["monitors"] = monitors;
    saveConfig();
}

json configurator::createJsonWallpaper(wallpaper* img) {
    json imageJson;
    imageJson["name"] = img->name;
    imageJson["fullPath"] = img->fullPath;
    imageJson["size"] = img->size;
    return imageJson;
}

void configurator::addWallpaper(wallpaper* img, imageType type) {
    if (isImageExistInConfig(img)) {
        return;
    }

    json imageJson = createJsonWallpaper(img);

    if (type == WALLPAPER_MANAGER)
        config["images"].push_back(imageJson);
    else
        config["scheduler"]["playlist"].push_back(imageJson);

    saveConfig();
}

void configurator::addWallpapers(std::vector<wallpaper> wallpapers, imageType type) {
    for (auto wallpaper : wallpapers) {
        if (isImageExistInConfig(&wallpaper))
            continue;

        json imageJson = createJsonWallpaper(&wallpaper);
        if (type == WALLPAPER_MANAGER)
            config["images"].push_back(imageJson);
        else
            config["scheduler"]["playlist"].push_back(imageJson);
    }

    saveConfig();
}

void configurator::removeWallpaper(wallpaper* img, imageType type) {
    if (isImageExistInConfig(img)) {
        return;
    }

    auto& target = type == WALLPAPER_MANAGER ? config["images"]
                                             : config["scheduler"]["playlist"];

    for (auto it = target.begin(); it != target.end(); ++it) {
        if (it->at("fullPath") == img->fullPath) {
            target.erase(it);
            return;
        }
    }

    std::cout << "Key '" << img->fullPath << "' not found in the JSON."
              << std::endl;
}

void configurator::removeWallpaper(uint index, imageType type) {
    auto& target = type == WALLPAPER_MANAGER ? config["images"]
                                             : config["scheduler"]["playlist"];

    target.erase(target.begin() + index);
}

json configurator::getConfig() { return config; }

void configurator::setImageSchedulerType(bool type) {
    config["scheduler"]["isRandomImage"] = type;
    saveConfig();
}

std::string configurator::getMonitors() {
    auto result = config["monitors"];
    return result;
}

bool configurator::isImageExistInConfig(wallpaper* img) {
    std::ifstream file(configPath);
    json jsonData;

    if (file.is_open()) {
        try {
            file >> jsonData;
            for (const auto& item : jsonData["images"]) {
                if (item.is_object() && item.contains("fullPath") && item["fullPath"] == img->fullPath)
                    return true;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error reading JSON: " << e.what() << std::endl;
            return false;
        }
    }
    return false;
}

void configurator::saveConfig() {
    std::ofstream file(configPath);
    file << config.dump(4);
    file.close();
}