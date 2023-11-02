#include <gtkmm.h>
#include <iostream>

class mainWindow : public Gtk::Window {
public:
  mainWindow();
  virtual ~mainWindow(){};

protected:
  void exit();
  void setRandomImage();
  void refresh();

private:
};
