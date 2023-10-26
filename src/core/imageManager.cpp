#include "../../include/imageManager.h"
#include "../../include/utils.h"

void image::printFileDetails() {
    std::cout << "name: " << image::name << std::endl;
    std::cout << "path: " << image::fullPath << std::endl;
    std::cout << "size: " << image::size << std::endl;
}

imageManager::imageManager(std::string imagesDirectoryPath) {
    this->imagesDirectoryPath = imagesDirectoryPath;
    addImages(imagesDirectoryPath);
}

imageManager::imageManager(configurator* conf){
    this->conf = conf;
    monitors = conf->getMonitors();
    images = conf->getImagesFromConfig();
    imageCount = images.size();
}

bool imageManager::isImageExist(std::string imagePath){
    for(auto image : images){
        if(image.fullPath == imagePath)
            return true;
    }
    return false;
}

int imageManager::getImagesCount(){
    return imageCount;
}

std::vector<image> imageManager::getImages(){
    return images;
}

image* imageManager::getImage(std::string imagePath){
    if (!fs::is_regular_file(imagePath))
        return nullptr;
    
    image *img = new image();
    img->fullPath = imagePath;
    img->name = utils::getFileName(imagePath);
    img->size = utils::getFileSize(imagePath);

    return img;
}

void imageManager::addImage(image* img) {
    if(!isImageExist(img->fullPath)){
        images.push_back(*img);
        imageCount++;
    }
}

//TODO: add check if it is image (.png .jpg etc...)
std::vector<image> imageManager::getFilesInDirectory(std::string& directoryPath) {
    std::vector<image> images;
    for (const auto &entry : fs::directory_iterator(directoryPath)) {
        if (fs::is_regular_file(entry)) {
            image* img = new image();
            img->fullPath = entry.path().string();
            img->name = entry.path().filename();
            img->size = entry.file_size();

            images.push_back(*img);
        }
    }
    return images;
}

bool imageManager::isValidImagesDirectory(std::string pathToDirectory){
     if(!fs::is_directory(pathToDirectory)){
        std::cerr << pathToDirectory << " is not directory" << std::endl;
        return false;
    }

    std::vector<image> images = getFilesInDirectory(pathToDirectory);
    if(images.empty()){
        std::cerr << pathToDirectory << " directory is emtpy." << std::endl;
        return false;
    }

    return true;
}

void imageManager::addImages(std::string imagesDirectoryPath) {
    if(isValidImagesDirectory(imagesDirectoryPath)){
        auto images = getFilesInDirectory(imagesDirectoryPath);
        for (auto image : images) {
            conf->addImage(&image, IMAGE_MANAGER);
            imageManager::images.push_back(image);
            imageCount++;
        }
    } else {
        std::cout << "Directory is not valid." << std::endl;
    }
}


std::vector<image> imageManager::getImages(std::string imagesDirectoryPath){
    if(isValidImagesDirectory(imagesDirectoryPath))
        return getFilesInDirectory(imagesDirectoryPath);
    else 
        std::cout << "Directory is not valid." << std::endl;
}

void imageManager::deleteImage(image* img) {
    if(!isImageExist(img->fullPath)){
        std::cerr << "File doesn't exist." << std::endl;
        return;
    }

    for(auto image : images){
        if(image.fullPath == img->fullPath){
            images.erase(utils::getItemIndexInVector(images, img));
            imageCount--;
            return;
        }
    }
}

void imageManager::deleteImage(int index){
    if(index <= images.size() - 1){
        images.erase(images.begin() + index);
        conf->removeImage(index, IMAGE_MANAGER);
        imageCount--;
    }
}

void imageManager::clearImages() {
    for(auto image : images)
        conf->removeImage(&image, IMAGE_MANAGER);
    
    images.clear();
    imageCount = images.size();
}
