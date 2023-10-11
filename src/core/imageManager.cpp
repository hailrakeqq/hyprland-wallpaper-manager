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

void imageManager::addImage(std::string imagePath) {
    image *img = (image*)malloc(sizeof(image*));
    img->fullPath = imagePath;
    img->name = getFileName(imagePath);
    img->size = getFileSize(imagePath);
    
    images.push_back(*img);
}

void imageManager::addImages(std::string imagesDirectoryPath) {
    
}

void imageManager::deleteImage(std::string imageName) {

}

void imageManager::clearImages(std::vector<image> images) {

}

image imageManager::getRandomImage() {

}