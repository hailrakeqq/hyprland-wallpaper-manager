#ifndef GUI_H
#define GUI_H

#include "configurator.h"
#include "imageManager.h"
#include "scheduler.h"
#include "wallpaperChanger.h"
#include <gtkmm.h>

#define MAX_COLUMN 4

struct itemPosition {
    int column;
    int row;
};

class gui {
public:
    gui(configurator* conf, imageManager* im, scheduler* s);
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

    // TODO: ця функція буде заповнювати таблицю grid картинками з вектору im,
    // playlist
    void imageLoader();

    void testRemoveItemFromGrid();
    void testAddItemToGrid();

private:
    Gtk::Grid* imagesMatrix;
    Gtk::Window* mainwindow;
    configurator* conf;
    imageManager* im;
    scheduler* s;
    itemPosition lastItemPosition{-1, 0};

    void onImageClick(Glib::ustring filename, int n_press, double x, double y);
    void insertImage(image* img);
    void removeImage(u_int8_t column, int row);
};
#endif // !GUI_H