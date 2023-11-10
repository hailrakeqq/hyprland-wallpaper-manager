#include "../../include/settings_ui.h"

settings_ui::settings_ui() { }

void settings_ui::initSettingsWindow(std::string& monitors) {
    auto refBuilderDialog = Gtk::Builder::create();

    try {
#ifdef DEBUG
        const std::string uiFilePath = "../ui/settings.ui";
#else
        const std::string uiFilePath = "/usr/share/hyprland-wallpaper-manager/ui/settings.ui";
#endif
        refBuilderDialog->add_from_file(uiFilePath);
    } catch (const Glib::FileError& ex) {
        std::cerr << "FileError: " << ex.what() << std::endl;
        return;
    } catch (const Glib::MarkupError& ex) {
        std::cerr << "MarkupError: " << ex.what() << std::endl;
        return;
    } catch (const Glib::Error& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return;
    } catch (...) {
        return;
        std::cerr << "Unexpected error during file loading." << std::endl;
    }

    settingsWindow = refBuilderDialog->get_widget<Gtk::Window>("settings_window");

    if (!settingsWindow) {
        std::cerr << "Could not get the dialog window" << std::endl;
        return;
    }

    auto pDialogCancelBtn = refBuilderDialog->get_widget<Gtk::Button>("cancel_btn");
    auto pDialogSaveBtn = refBuilderDialog->get_widget<Gtk::Button>("save_btn");
    auto pDialogEntryString = refBuilderDialog->get_widget<Gtk::Entry>("inputMonitor");

    if (pDialogCancelBtn)
        pDialogCancelBtn->signal_clicked().connect([this]() { closeSettingsDialog(); });
    if (pDialogSaveBtn)
        pDialogSaveBtn->signal_clicked().connect([this, pDialogEntryString, &monitors]() {
            std::string monitorsFromEntry = pDialogEntryString->get_text();
            if (conf != nullptr)
                conf->updateMonitors(monitorsFromEntry);
            else if (monitors != "default value")
                monitors = monitorsFromEntry;

            closeSettingsDialog();
        });

    settingsWindow->set_visible(true);
}

void settings_ui::setConfigurator(configurator* config) {
    conf = config;
}

void settings_ui::closeSettingsDialog() {
    if (settingsWindow) {
        delete settingsWindow;
    }
}