#ifndef TUI_H
#define TUI_H

#include "imageManager.h"
#include "scheduler.h"
#include "wallpaperChanger.h"
#include <iostream>
#include <vector>

class tui {
public:
  tui(imageManager &im, scheduler &s, configurator &conf);
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
  imageManager &im;
  scheduler &s;
  configurator &conf;
};

#endif // !TUI_H