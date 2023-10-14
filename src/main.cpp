#include <iostream>
#include "../include/imageManager.h"
#include "../include/wallpaperChanger.h"
#include "../include/configurator.h"

int main(){
    auto config = configurator("config.json");
    auto im = imageManager(&config);
    auto images = im.getImages();
    for (int i = 0; i < images.size(); i++){
        images[i].printFileDetails();
    }
    std::cout << im.getImagesCount() << std::endl;

    return 0;
}