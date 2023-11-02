#include "../../include/wallpaperChanger.h"

bool wallpaperChanger::setWallpaper(std::string monitors, image *img) {

  std::string command = "hyprctl hyprpaper preload " + img->fullPath +
                        " && hyprctl hyprpaper wallpaper " + monitors + "," +
                        img->fullPath;

  int result = std::system(command.c_str());

  return result == 0 ? true : false;
}
