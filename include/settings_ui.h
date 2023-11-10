#ifndef SETTINGS_UI_H
#define SETTINGS_UI_H

#include "configurator.h"
#include <gtkmm.h>

class configurator; // forward declaration

class settings_ui {
public:
    settings_ui();

    void initSettingsWindow(std::string& monitors);

    void setConfigurator(configurator* config);

private:
    void closeSettingsDialog();

    Gtk::Window* settingsWindow;
    configurator* conf;
};
#endif // !SETTINGS_UI_H