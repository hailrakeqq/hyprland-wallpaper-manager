#include "../../include/gui.h"

    class MyDialog : public Gtk::MessageDialog {
  public:
    MyDialog() : MessageDialog("Hello world!", false, Gtk::MessageType::INFO, Gtk::ButtonsType::OK, false) {
      set_secondary_text("This is an example dialog.");
      signal_response().connect(sigc::hide(sigc::mem_fun(*this, &Gtk::Window::destroy)));
    };
};
gui::gui(){}

int gui::test(int argc, char** argv){
    auto app = Gtk::Application::create();
    return app->make_window_and_run<MyDialog>(argc, argv);
}
