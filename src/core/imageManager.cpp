#include "../../include/imageManager.h"
#include "../utils.cpp"

void image::printFileDetails() {
    std::cout << "Image name: " << image::name << std::endl;
    std::cout << "Image path: " << image::fullPath << std::endl;
    std::cout << "Image size: " << image::size << std::endl;
}

imageManager::imageManager(std::string imagesDirectoryPath) {
    this->imagesDirectoryPath = imagesDirectoryPath;
    addImages(imagesDirectoryPath);
    imageCount = images.size();
}

bool imageManager::isImageExist(std::string imagePath){
    for(auto image : images){
        if(image.fullPath == imagePath)
            return true;
    }
    return false;
}

image* imageManager::getImage(std::string imagePath){
    if (!fs::is_regular_file(imagePath))
        return nullptr;
    
    image *img = (image *)malloc(sizeof(image));
    img->fullPath = imagePath;
    img->name = getFileName(imagePath);
    img->size = getFileSize(imagePath);

    return img;
}

void imageManager::addImage(image* img) {
    if(isImageExist(img->fullPath)){
        images.push_back(*img);
        imageCount++;
    }
}

std::vector<image> imageManager::getFilesInDirectory(std::string& directoryPath) {
    std::vector<image> images;
    for (const auto &entry : fs::directory_iterator(directoryPath)) {
        if (fs::is_regular_file(entry)) {
            image *img = (image *)malloc(sizeof(image));
            img->fullPath = entry.path();
            img->name = entry.path().filename();
            img->size = entry.file_size();

            images.push_back(*img);
        }
    }
    return images;
}

void imageManager::addImages(std::string imagesDirectoryPath) {
    if(!fs::is_directory(imagesDirectoryPath)){
        std::cerr << imagesDirectoryPath << " is not directory" << std::endl;
        return;
    }

    std::vector<image> images = getFilesInDirectory(imagesDirectoryPath);
    if(images.empty()){
        std::cerr << imagesDirectoryPath << " directory is emtpy." << std::endl;
        return;
    }

    for(auto image : images){
        imageManager::images.push_back(image);
        imageCount++;
    }
}

void imageManager::deleteImage(image* img) {
    if(!isImageExist(img->fullPath)){
        std::cerr << "File doesn't exist." << std::endl;
    }

    for(auto image : images){
        if(image.fullPath == img->fullPath){
            images.erase(getItemIndexInVector(images, img));
            imageCount--;
            return;
        }
    }
}

void imageManager::clearImages(std::vector<image>* images) {
    images->clear();
}

image* imageManager::getRandomImage() {
    if(imageCount == 0){
        return nullptr;
    }
    int randomIndex = rand() % imageCount;
    return &images.at(randomIndex);
}