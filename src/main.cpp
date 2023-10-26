#include <iostream>
#include "../include/configurator.h"
#include "../include/cmdUI.h"
#include "../include/scheduler.h"

int main()
{
    auto config = configurator("config.json");
    auto im = imageManager(&config);

    auto sched = new scheduler(&config, &im);

    auto menu = cmdUI(im, *sched, config);
    menu.renderMenu();
    return 0;
}