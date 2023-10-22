#include <iostream>
#include "../include/configurator.h"
#include "../include/cmdUI.h"
#include "../include/scheduler.h"

int main()
{
    // auto config = configurator("config.json");
    // auto im = imageManager(&config);

    // auto sched = new scheduler("2.0", &config, &im);

    // auto images = im.getImages();

    // for (auto image : images){
    //     sched->addImageToPlaylist(&image);
    //     config.addImageToConfig(&image);
    // }

    // json schedulerJson = sched->toJson();
    // std::cout << schedulerJson.dump(4) << std::endl;
    
    // config.updateScheduler(schedulerJson);

    // auto menu = cmdUI(im);
    // menu.renderMenu();

    return 0;
}