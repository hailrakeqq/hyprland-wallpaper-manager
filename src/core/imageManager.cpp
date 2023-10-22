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
        imageCount--;
    }
}

void imageManager::clearImages() {
    images.clear();
    imageCount = images.size();
}

image* imageManager::getRandomImage() {
    if(imageCount == 0){
        return nullptr;
    }
    int randomIndex = rand() % imageCount;
    return &images.at(randomIndex);
}