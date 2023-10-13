#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <iostream>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

typedef struct {
    std::string name;
    std::string fullPath;
    long size;

    void printFileDetails();
} image;

class imageManager {
public:
    imageManager(std::string imagesDirectoryPath);
    int getImagesCount();
    std::vector<image> getImages();
    bool isImageExist(std::string imagePath);
    image *getImage(std::string imagePath);
    void addImage(image *img);
    void addImages(std::string imagesDirectoryPath);
    void deleteImage(image* img);
    void deleteImage(int index);
    void clearImages();
    image *getRandomImage();

private:
    int imageCount;
    std::string imagesDirectoryPath;
    std::vector<image> images;

    std::vector<image> getFilesInDirectory(std::string &directoryPath);
};
#endif // !IMAGEMANAGER_H