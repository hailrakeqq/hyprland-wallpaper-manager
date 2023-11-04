#include "../include/configurator.h"

configurator::configurator(std::string configFilePath) {
    configPath = configFilePath;
    if (fs::is_regular_file(configFilePath)) {
        std::ifstream fileStream(configFilePath);
        fileStream >> config;
        fileStream.close();
        return;
    }

    std::cout << "Enter monitor(s) on which you want set wallpaper(example "
                 "\"DP-1, DP-2\"): ";
    std::string monitorInput;
    std::getline(std::cin, monitorInput);

    if (!monitorInput.empty())
        config["monitors"] = monitorInput;
    else
        std::cout << "Input is empty. Please provide a valid input." << std::endl;

    config["images"] = json::array();
    config["scheduler"] = json::object();
    saveConfig();
}

void configurator::updateMonitors(std::string monitors) {
    config["monitors"] = monitors;
    saveConfig();
}

std::vector<image> configurator::getImagesFromConfig() {
    std::vector<image> images;

    for (auto jsonImage : configurator::config["images"]) {
        image img;
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

json configurator::createJsonImage(image* img) {
    json imageJson;
    imageJson["name"] = img->name;
    imageJson["fullPath"] = img->fullPath;
    imageJson["size"] = img->size;
    return imageJson;
}

void configurator::addImage(image* img, imageType type) {
    if (isImageExistInConfig(img)) {
        std::cout << "Image '" << img->fullPath << "' already exist in JSON."
                  << std::endl;
        return;
    }

    json imageJson = createJsonImage(img);
    // auto target = type == IMAGE_MANAGER ? config["images"] :
    // config["scheduler"]["playlist"];
    if (type == IMAGE_MANAGER) {
        config["images"].push_back(imageJson);
    } else {
        config["scheduler"]["playlist"].push_back(imageJson);
    }
    saveConfig();
}

void configurator::removeImage(image* img, imageType type) {
    if (isImageExistInConfig(img)) {
        std::cout << "Image '" << img->fullPath << "' is not exist in the JSON."
                  << std::endl;
        return;
    }

    auto& target = type == IMAGE_MANAGER ? config["images"]
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

void configurator::removeImage(uint index, imageType type) {
    auto& target = type == IMAGE_MANAGER ? config["images"]
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

bool configurator::isImageExistInConfig(image* img) {
    std::ifstream file("config.json");
    json jsonData;

    if (file.is_open()) {
        try {
            file >> jsonData;
        } catch (const std::exception& e) {
            std::cerr << "Error reading JSON: " << e.what() << std::endl;
            return 1;
        }

        return jsonData.contains(img->fullPath) ? true : false;
    }
}

void configurator::saveConfig() {
    std::ofstream file(configPath);
    file << config.dump(4);
    file.close();
}