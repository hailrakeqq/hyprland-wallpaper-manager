#include <iostream>
#include "../include/configurator.h"
#include "../include/gui.h"
#include "../include/tui.h"
#include "../include/scheduler.h"

int main(int argc, char** argv)
{
    auto config = configurator("config.json");
    auto im = imageManager(&config);

    auto sched = new scheduler(&config, &im);

#ifdef COMPILE_GUI
    auto guiMenu = gui();
    guiMenu.test(argc, argv);
#else
    auto tuiMenu = tui(im, *sched, config);
    tuiMenu.renderMenu();
#endif

    return 0;
}