#include "../../include/mainWindow.h"

void mainWindow::exit() { std::cout << "test message: exit" << std::endl; }

void mainWindow::setRandomImage() {
  std::cout << "test message: set random image" << std::endl;
}

void mainWindow::refresh() {
  std::cout << "test message: refresh" << std::endl;
}

mainWindow::mainWindow() {

#pragma region button
  auto btnbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 5);

  Gtk::Button exitBtn;
  Gtk::Button refreshBtn;
  Gtk::Button randomBtn;

  auto exitLabel = Gtk::make_managed<Gtk::Label>("Exit");
  auto refreshLabel = Gtk::make_managed<Gtk::Label>("Refresh");
  auto randomLabel = Gtk::make_managed<Gtk::Label>("Random");

  exitBtn.set_child(*exitLabel);
  refreshBtn.set_child(*refreshLabel);
  randomBtn.set_child(*randomLabel);

  refreshBtn.signal_clicked().connect(
      sigc::mem_fun(*this, &mainWindow::refresh));
  randomBtn.signal_clicked().connect(
      sigc::mem_fun(*this, &mainWindow::setRandomImage));
  exitBtn.signal_clicked().connect(sigc::mem_fun(*this, &mainWindow::exit));

  exitBtn.set_margin(10);
  refreshBtn.set_margin(10);
  randomBtn.set_margin(10);

  btnbox->append(exitBtn);
  btnbox->append(refreshBtn);
  btnbox->append(randomBtn);

  set_child(*btnbox);

#pragma endregion
}