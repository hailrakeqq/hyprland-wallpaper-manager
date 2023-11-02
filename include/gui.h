#ifndef GUI_H
#define GUI_H

#include "../include/mainWindow.h"
#include "imageManager.h"
#include "scheduler.h"
#include <gtkmm.h>

#define MAX_COLUMN 4

struct itemPosition {
  int column;
  int row;
};

class gui {
public:
  Glib::RefPtr<Gtk::Application> app;
  gui(imageManager *im, scheduler *s);
  int8_t on_app_activate();
  void run(int argc, char **argv);

protected:
  void on_file_dialog_response(int response_id, Gtk::FileChooserDialog *dialog);
  void on_folder_dialog_response(int response_id,
                                 Gtk::FileChooserDialog *dialog);
  void addWallpaper(Gtk::Window &mainWindow);
  void addWallpaperDirectory(Gtk::Window &mainWindow);
  void refresh();
  void setRandom();
  void exit();

  void testRemoveItemFromGrid();
  void testAddItemToGrid();

private:
  Gtk::Grid *imagesMatrix;
  Gtk::Window *mainwindow;
  imageManager *im;
  scheduler *s;
  itemPosition lastItemPosition{-1, 0};
};
#endif // !GUI_H