#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <iostream>
#include <vector>

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
    void addImage(std::string imagePath);
    void addImages(std::string imagesDirectoryPath);
    void deleteImage(std::string imageName);
    void clearImages(std::vector<image> images);
    image getRandomImage();

private:
    int imageCount;
    std::string imagesDirectoryPath;
    std::vector<image> images;
};
#endif // !IMAGEMANAGER_H