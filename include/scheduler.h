#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <chrono>
#include <string>
#include <thread>
#include <vector>

#include "configurator.h"
#include "image.h"
#include "utils.h"
#include "wallpaperChanger.h"

class scheduler {
public:
    scheduler(configurator* conf, imageManager* im);
    scheduler(std::string interval, configurator* conf, imageManager* im);

    json toJson();

    void addImageToPlaylist(image* img);
    void removeImageFromPlaylist(image* img);
    void removeImageFromPlaylist(uint index);
    int playlistSize();

    image getCurrentImage();
    void setCurrentImage(image* img);

    bool isRandomImage();
    void setRandomImage();

    void start();
    void scheduleImage();
    void stop();
    void changeInterval(std::string interval);

    std::vector<image> getPlaylist();

private:
    configurator* conf;
    imageManager* im;
    bool isSchedulerRun;
    bool randomImage;
    std::vector<image> playlist;
    image currentImage;
    uint currentImageIndex;
    int interval;
};

#endif // !SCHEDULER_H