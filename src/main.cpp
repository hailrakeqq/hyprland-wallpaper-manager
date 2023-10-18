#include <iostream>
#include "../include/configurator.h"
#include "../include/cmdUI.h"

int main(){
    auto config = configurator("config.json");
    auto im = imageManager(&config);
    auto menu = cmdUI(im);
    menu.renderMenu();
    return 0;
}