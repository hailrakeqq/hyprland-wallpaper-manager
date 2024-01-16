#include "../../include/wallpaperManager.h"

void wallpaper::printFileDetails() {
    std::cout << "name: " << wallpaper::name << std::endl;
    std::cout << "path: " << wallpaper::fullPath << std::endl;
    std::cout << "size: " << wallpaper::size << std::endl;
}

wallpaperManager::wallpaperManager(std::string wallpapersDirectoryPath) {
    this->wallpapersDirectoryPath = wallpapersDirectoryPath;
    addWallpapers(wallpapersDirectoryPath);
}

wallpaperManager::wallpaperManager(configurator* conf) {
    this->conf = conf;
    monitors = conf->getMonitors();
    addWallpapers(conf->getWallpapersFromConfig());
    wallpaperCount = wallpapers.size();
}

bool wallpaperManager::isWallpaperExist(std::string wallpaperPath) {
    for (auto image : wallpapers) {
        if (image.fullPath == wallpaperPath)
            return true;
    }
    return false;
}

int wallpaperManager::getImagesCount() { return wallpaperCount; }

std::vector<wallpaper> wallpaperManager::getImages() { return wallpapers; }

wallpaper* wallpaperManager::getWallpaper(std::string wallpaperPath) {
    if (!fs::is_regular_file(wallpaperPath))
        return nullptr;

    wallpaper* img = new wallpaper();
    img->fullPath = wallpaperPath;
    img->name = utils::getFileName(wallpaperPath);
    img->size = utils::getFileSize(wallpaperPath);
    img->lastModifiedTimet = utils::getLastModifiedTime(wallpaperPath);

    return img;
}

void wallpaperManager::addWallpaper(wallpaper* wallpaper) {
    if (!isWallpaperExist(wallpaper->fullPath)) {
        wallpapers.push_back(*wallpaper);
        wallpaperCount++;
    }
}

void wallpaperManager::addWallpapers(std::vector<wallpaper> wallpapers) {
    for (auto wallpaper : wallpapers) {
        if (!isWallpaperExist(wallpaper.fullPath)) {
            this->wallpapers.push_back(wallpaper);
            wallpaperCount++;
        }
    }
}

std::vector<wallpaper>
wallpaperManager::getFilesInDirectory(std::string& directoryPath) {
    std::vector<wallpaper> images;
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        const std::string fileExtension = entry.path().extension();
        if (fs::is_regular_file(entry) && (fileExtension == ".jpeg" || fileExtension == ".jpg" || fileExtension == ".png")) {
            wallpaper* img = new wallpaper();
            img->fullPath = entry.path().string();
            img->name = entry.path().filename();
            img->size = entry.file_size();

            img->lastModifiedTimet = utils::getLastModifiedTime(entry.path().string());

            images.push_back(*img);
        }
    }
    return images;
}

bool wallpaperManager::isValidWallpapersDirectory(std::string pathToDirectory) {
    if (!fs::is_directory(pathToDirectory)) {
        std::cerr << pathToDirectory << " is not directory" << std::endl;
        return false;
    }

    std::vector<wallpaper> images = getFilesInDirectory(pathToDirectory);
    if (images.empty()) {
        std::cerr << pathToDirectory << " directory is emtpy." << std::endl;
        return false;
    }

    return true;
}

void wallpaperManager::addWallpapers(std::string imagesDirectoryPath) {
    if (isValidWallpapersDirectory(imagesDirectoryPath)) {
        auto images = getFilesInDirectory(imagesDirectoryPath);
        for (auto image : images) {
            conf->addWallpaper(&image, WALLPAPER_MANAGER);
            wallpaperManager::wallpapers.push_back(image);
            wallpaperCount++;
        }
    } else {
        std::cout << "Directory is not valid." << std::endl;
    }
}

std::vector<wallpaper> wallpaperManager::getWallpapers(std::string imagesDirectoryPath) {
    if (isValidWallpapersDirectory(imagesDirectoryPath))
        return getFilesInDirectory(imagesDirectoryPath);
    else
        std::cout << "Directory is not valid." << std::endl;
}

std::vector<wallpaper> wallpaperManager::getWallpapers() {
    return wallpapers;
}

void wallpaperManager::deleteWallpaper(wallpaper* img) {
    if (!isWallpaperExist(img->fullPath)) {
        std::cerr << "File doesn't exist." << std::endl;
        return;
    }

    for (auto wallpaper : wallpapers) {
        if (wallpaper.fullPath == img->fullPath) {
            wallpapers.erase(utils::getItemIndexInVector(wallpapers, img));
            wallpaperCount--;
            return;
        }
    }
}

void wallpaperManager::deleteWallpaper(int index) {
    if (index <= wallpapers.size() - 1) {
        wallpapers.erase(wallpapers.begin() + index);
        conf->removeWallpaper(index, WALLPAPER_MANAGER);
        wallpaperCount--;
    }
}

void wallpaperManager::updateWallpapers(std::vector<wallpaper>& wallpapers) {
    this->wallpapers = wallpapers;
}

void wallpaperManager::clearWallpapers() {
    wallpapers.clear();
    wallpaperCount = wallpapers.size();
}
