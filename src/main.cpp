#include "../include/configurator.h"
#include "../include/gui.h"
#include "../include/scheduler.h"
#include "../include/tui.h"
#include <iostream>

int main(int argc, char **argv) {
  auto config = new configurator("config.json");
  auto im = new imageManager(config);

  auto sched = new scheduler(config, im);

#ifdef COMPILE_GUI
  auto g = new gui(config, im, sched);
  g->run(argc, argv);

#else
  auto tuiMenu = tui(im, *sched, config);
  tuiMenu.renderMenu();
#endif

  return 0;
}