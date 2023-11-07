#ifndef GUI_H
#define GUI_H

#include "configurator.h"
#include "scheduler.h"
#include "wallpaperChanger.h"
#include "wallpaperManager.h"
#include <gtkmm.h>

#define MAX_COLUMN 4

struct itemPosition {
    int column;
    int row;
};

class gui {
public:
    gui(configurator* conf, wallpaperManager* wm, scheduler* s);
    Glib::RefPtr<Gtk::Application> app;
    int8_t on_app_activate();
    void run(int argc, char** argv);

protected:
    void on_file_dialog_response(int response_id, Gtk::FileChooserDialog* dialog);
    void on_folder_dialog_response(int response_id,
        Gtk::FileChooserDialog* dialog);
    void addWallpaper(Gtk::Window& mainWindow);
    void addWallpaperDirectory(Gtk::Window& mainWindow);
    void refresh();
    void setRandom();

    void wallpaperLoader();
    int getItemInMatrix();

private:
    Gtk::Grid* wallpapersMatrix;
    Gtk::Window* mainwindow;
    Gtk::Dialog* monitorSetDialog;
    configurator* conf;
    wallpaperManager* wm;
    scheduler* s;
    itemPosition lastItemPosition{-1, 0};

    void clearMatrix();
    void onWallpaperClick(Glib::ustring filename, int n_press, double x, double y);
    void insertWallpaper(wallpaper* img);
    void removeWallpaper(u_int8_t column, int row);
};
#endif // !GUI_H