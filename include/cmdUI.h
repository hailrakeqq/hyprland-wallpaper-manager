#ifndef CMDUI_H
#define CMDUI_H

#include <iostream>
#include <vector>
#include "imageManager.h"
#include "wallpaperChanger.h"
#include "scheduler.h"

class cmdUI{
public:
    cmdUI(imageManager &im, scheduler &s);
    void renderMenu();
    void addImages();
    void showImages();
    void changeImage();
    void setRandom();
    void schedulerMenu();
    void showPlaylist();
    void changeInterval();

private:
    imageManager& im;
    scheduler &s;
};

#endif // !CMDUI_H