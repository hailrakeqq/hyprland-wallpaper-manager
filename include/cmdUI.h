#ifndef CMDUI_H
#define CMDUI_H

#include <iostream>
#include <vector>
#include "imageManager.h"
#include "wallpaperChanger.h"

class cmdUI{
public:
    cmdUI(imageManager &im);
    void renderMenu();
    void showImages();
    void changeImage();

private:
    imageManager& im;
};

#endif // !CMDUI_H