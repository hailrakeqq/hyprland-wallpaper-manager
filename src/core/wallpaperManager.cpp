#include "../../include/wallpaperManager.h"

void wallpaper::printFileDetails() {
    std::cout << "name: " << wallpaper::name << std::endl;
    std::cout << "path: " << wallpaper::fullPath << std::endl;
    std::cout << "size: " << wallpaper::size << std::endl;
}

wallpaperManager::wallpaperManager(std::string imagesDirectoryPath) {
    this->imagesDirectoryPath = imagesDirectoryPath;
    addImages(imagesDirectoryPath);
}

wallpaperManager::wallpaperManager(configurator* conf) {
    this->conf = conf;
    monitors = conf->getMonitors();
    wallpapers = conf->getImagesFromConfig();
    wallpaperCount = wallpapers.size();
}

bool wallpaperManager::isImageExist(std::string imagePath) {
    for (auto image : wallpapers) {
        if (image.fullPath == imagePath)
            return true;
    }
    return false;
}

int wallpaperManager::getImagesCount() { return wallpaperCount; }

std::vector<wallpaper> wallpaperManager::getImages() { return wallpapers; }

wallpaper* wallpaperManager::getImage(std::string imagePath) {
    if (!fs::is_regular_file(imagePath))
        return nullptr;

    wallpaper* img = new wallpaper();
    img->fullPath = imagePath;
    img->name = utils::getFileName(imagePath);
    img->size = utils::getFileSize(imagePath);

    return img;
}

void wallpaperManager::addImage(wallpaper* img) {
    if (!isImageExist(img->fullPath)) {
        wallpapers.push_back(*img);
        wallpaperCount++;
    }
}

// TODO: add check if it is image (.png .jpg etc...)
std::vector<wallpaper>
wallpaperManager::getFilesInDirectory(std::string& directoryPath) {
    std::vector<wallpaper> images;
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        if (fs::is_regular_file(entry)) {
            wallpaper* img = new wallpaper();
            img->fullPath = entry.path().string();
            img->name = entry.path().filename();
            img->size = entry.file_size();

            images.push_back(*img);
        }
    }
    return images;
}

bool wallpaperManager::isValidImagesDirectory(std::string pathToDirectory) {
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

void wallpaperManager::addImages(std::string imagesDirectoryPath) {
    if (isValidImagesDirectory(imagesDirectoryPath)) {
        auto images = getFilesInDirectory(imagesDirectoryPath);
        for (auto image : images) {
            conf->addImage(&image, IMAGE_MANAGER);
            wallpaperManager::wallpapers.push_back(image);
            wallpaperCount++;
        }
    } else {
        std::cout << "Directory is not valid." << std::endl;
    }
}

std::vector<wallpaper> wallpaperManager::getImages(std::string imagesDirectoryPath) {
    if (isValidImagesDirectory(imagesDirectoryPath))
        return getFilesInDirectory(imagesDirectoryPath);
    else
        std::cout << "Directory is not valid." << std::endl;
}

void wallpaperManager::deleteImage(wallpaper* img) {
    if (!isImageExist(img->fullPath)) {
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

void wallpaperManager::deleteImage(int index) {
    if (index <= wallpapers.size() - 1) {
        wallpapers.erase(wallpapers.begin() + index);
        conf->removeWallpaper(index, IMAGE_MANAGER);
        wallpaperCount--;
    }
}

void wallpaperManager::clearImages() {
    for (auto wallpaper : wallpapers)
        conf->removeWallpaper(&wallpaper, IMAGE_MANAGER);

    wallpapers.clear();
    wallpaperCount = wallpapers.size();
}
