#ifndef TUI_H
#define TUI_H

#include "scheduler.h"
#include "wallpaperChanger.h"
#include "wallpaperManager.h"
#include <iostream>
#include <vector>

class tui {
public:
    tui(wallpaperManager& wm, scheduler& s, configurator& conf);
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
    wallpaperManager& wm;
    scheduler& s;
    configurator& conf;
};

#endif // !TUI_H