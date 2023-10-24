#include "../include/configurator.h"

configurator::configurator(std::string configFilePath){
    configPath = configFilePath;
    if(fs::is_regular_file(configFilePath)){
        std::ifstream fileStream(configFilePath);
        fileStream >> config;
        fileStream.close();
        return;
    }
    
    std::cout << "Enter monitor(s) on which you want set wallpaper(example \"DP-1, DP-2\"): ";
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

std::vector<image> configurator::getImagesFromConfig()
{
    std::vector<image> images;
   
    for (auto jsonImage : configurator::config["images"])
    {
        image img;
        img.fullPath = jsonImage["fullPath"];
        img.name = jsonImage["name"];
        img.size = jsonImage["size"];

        images.push_back(img);
    }

    return images;
}

void configurator::updateScheduler(json &scheduler){
    config["scheduler"] = scheduler;
    saveConfig();
}

void configurator::addImageToConfig(image *img){
    if(isImageExistInConfig(img)){
        std::cout << "Image '" << img->fullPath << "' already exist in JSON." << std::endl;
        return;
    }

    json imageJson;
    imageJson["name"] = img->name;
    imageJson["fullPath"] = img->fullPath;
    imageJson["size"] = img->size;

    config["images"].push_back(imageJson);
    saveConfig();
}

void configurator::removeImageFromConfig(image *img){
    if(isImageExistInConfig(img)){
        std::cout << "Image '" << img->fullPath << "' is not exist in the JSON." << std::endl;
        return;
    }

    for (auto it = config["images"].begin(); it != config["images"].end(); ++it) {
        if (it->at("fullPath") == img->fullPath) {
            config["images"].erase(it);
            saveConfig();
            return;
        }
    }
    std::cout << "Key '" << img->fullPath << "' not found in the JSON." << std::endl;
}

json configurator::getConfig(){
    return config;
}

std::string configurator::getMonitors(){
    auto result = config["monitors"];
    return result;
}

bool configurator::isImageExistInConfig(image *img){
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