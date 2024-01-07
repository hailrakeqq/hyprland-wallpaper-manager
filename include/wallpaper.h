#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <time.h>
typedef struct {
    std::string name;
    std::string fullPath;
    long size;
    time_t lastModifiedTimet;

    void printFileDetails();
} wallpaper;
#endif // !IMAGE_H
