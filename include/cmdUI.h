#ifndef CMDUI_H
#define CMDUI_H

#include <iostream>
#include <vector>
#include "imageManager.h"
#include "wallpaperChanger.h"
#include "scheduler.h"

class cmdUI {
public:
    cmdUI(imageManager &im, scheduler &s, configurator &conf);
    void renderMenu();
    void showImages();
    void addImagesToImageManager();
    void addImagesToPlaylist();
    void addImageToPlaylist();
    void playlistSettings();
    void removeImageFromImageManager();
    void removeImageFromPlaylist();
    void changeImage();
    void setRandom();
    void schedulerMenu();
    void showPlaylist();
    void changeInterval();
    void changeDisplay();

private:
    imageManager& im;
    scheduler &s;
    configurator &conf;
};

#endif // !CMDUI_H