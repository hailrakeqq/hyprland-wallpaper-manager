#include <iostream>
#include "../include/configurator.h"
#include "../include/cmdUI.h"
#include "../include/scheduler.h"

int main()
{
    //TODO:написати тест до scheduler

    auto config = configurator("config.json");
    auto im = imageManager(&config);

    auto sched = new scheduler(&config, &im);

    // json schedulerJson = sched->toJson();
    // std::cout << schedulerJson.dump(4) << std::endl;
    
    // config.updateScheduler(schedulerJson);

    auto menu = cmdUI(im, *sched, config);
    menu.renderMenu();
    return 0;
}