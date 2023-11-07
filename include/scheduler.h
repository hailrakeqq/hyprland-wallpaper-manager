#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <chrono>
#include <string>
#include <thread>
#include <vector>

#include "configurator.h"
#include "utils.h"
#include "wallpaper.h"
#include "wallpaperChanger.h"

class scheduler {
public:
    scheduler(configurator* conf, wallpaperManager* wm);
    scheduler(std::string interval, configurator* conf, wallpaperManager* wm);

    json toJson();

    void addImageToPlaylist(wallpaper* img);
    void removeImageFromPlaylist(wallpaper* img);
    void removeImageFromPlaylist(uint index);
    int playlistSize();

    wallpaper getCurrentImage();
    void setCurrentImage(wallpaper* img);

    bool isRandomImage();
    void setRandomImage();

    void start();
    void scheduleImage();
    void stop();
    void changeInterval(std::string interval);

    std::vector<wallpaper> getPlaylist();

private:
    configurator* conf;
    wallpaperManager* wm;
    bool isSchedulerRun;
    bool randomImage;
    std::vector<wallpaper> playlist;
    wallpaper currentImage;
    uint currentImageIndex;
    int interval;
};

#endif // !SCHEDULER_H