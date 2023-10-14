#ifndef IMAGE_H
#define IMAGE_H

#include <string>
typedef struct {
    std::string name;
    std::string fullPath;
    long size;

    void printFileDetails();
} image;
#endif // !IMAGE_H
