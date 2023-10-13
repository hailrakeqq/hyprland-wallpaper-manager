#include "../../include/wallpaperChanger.h"

bool wallpaperChanger::setWallpaper(image* img) {
    std::string command = "qdbus org.kde.plasmashell /PlasmaShell org.kde.PlasmaShell.evaluateScript 'var allDesktops = desktops();"
    "print (allDesktops);"
    "for (i=0;i<allDesktops.length;i++) {d = allDesktops[i];d.wallpaperPlugin = \"org.kde.image\";"
    "d.currentConfigGroup = Array(\"Wallpaper\", \"org.kde.image\", \"General\");"
    "d.writeConfig(\"Image\",";

    command += "\"" + img->fullPath + "\")}\'";

    int result = std::system(command.c_str());

    return result == 0 ? true : false;  
}
