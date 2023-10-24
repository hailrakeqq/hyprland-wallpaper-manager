#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include <string>
#include <thread>
#include <chrono>

#include "image.h"
#include "configurator.h"
#include "utils.h"
#include "wallpaperChanger.h"

class scheduler {
public:
    scheduler(configurator *conf, imageManager *im);
    scheduler(std::string interval, configurator *conf, imageManager*im);

    json toJson();
    
    void addImageToPlaylist(image *img);
    void removeImageFromPlaylist(image *img);
    void removeImageFromPlaylist(uint index);

    image *getCurrentImage();
    void setCurrentImage(image* img);

    void start();
    void scheduleImage();
    void stop();
    void changeInterval(std::string interval);
    
    std::vector<image> getPlaylist();

private:
    configurator *conf;
    imageManager *im;
    bool isSchedulerRun;
    bool isRandomImage;
    std::vector<image> playlist;
    image *currentImage;
    uint currentImageIndex;
    int interval;
};

#endif // !SCHEDULER_H