#include "../../include/gui.h"

// TODO: add sorting

gui::gui(configurator *conf, imageManager *im, scheduler *s) {
  this->conf = conf;
  this->im = im;
  this->s = s;
}

void gui::onImageClick(Glib::ustring filename, int n_press, double x,
                       double y) {
  if (n_press == 1) {
    wallpaperChanger::setWallpaper(conf->getMonitors(), filename);
    std::cout << "Image clicked at x: " << x << ", y: " << y << std::endl;
  }
}

void gui::insertImage(image *img) {
  Gtk::Image imgFile(img->fullPath);
  imgFile.set_name(img->fullPath);
  if (lastItemPosition.column < MAX_COLUMN - 1) {
    imagesMatrix->attach(imgFile, ++lastItemPosition.column,
                         lastItemPosition.row);
  } else {
    imagesMatrix->insert_row(++lastItemPosition.row);
    lastItemPosition.column = -1;
    imagesMatrix->attach(imgFile, ++lastItemPosition.column,
                         lastItemPosition.row);
  }

  Glib::RefPtr<Gtk::GestureClick> refGesture = Gtk::GestureClick::create();
  refGesture->signal_pressed().connect(
      [this, refGesture](int n_press, double x, double y) {
        auto refWidget = refGesture->get_widget();
        auto filename = refWidget->get_name();
        onImageClick(filename, n_press, x, y);
        std::cout << filename << std::endl;
      });

  imgFile.add_controller(refGesture);
}

void gui::removeImage(uint8_t column, int row) {
  auto currentItem = imagesMatrix->get_child_at(column, row);

  if (lastItemPosition.column > 0) {
    imagesMatrix->remove(*currentItem);
    lastItemPosition.column--;
  } else {
    imagesMatrix->remove(*currentItem);
    lastItemPosition.column = MAX_COLUMN - 1;
    imagesMatrix->remove_row(lastItemPosition.row);
    lastItemPosition.row--;
  }
}

void gui::imageLoader() {
  for (auto img : im->getImages())
    insertImage(&img);
}

void gui::addWallpaperDirectory(Gtk::Window &window) {
  auto dialog = new Gtk::FileChooserDialog(
      "Please choose a folder", Gtk::FileChooser::Action::SELECT_FOLDER);
  dialog->set_transient_for(window);
  dialog->set_modal(true);
  dialog->signal_response().connect(sigc::bind(
      sigc::mem_fun(*this, &gui::on_folder_dialog_response), dialog));

  dialog->add_button("_Cancel", Gtk::ResponseType::CANCEL);
  dialog->add_button("Select", Gtk::ResponseType::OK);

  dialog->show();
}

void gui::addWallpaper(Gtk::Window &window) {
  auto dialog = new Gtk::FileChooserDialog("Please choose a file",
                                           Gtk::FileChooser::Action::OPEN);
  dialog->set_transient_for(window);
  dialog->set_modal(true);
  dialog->signal_response().connect(
      sigc::bind(sigc::mem_fun(*this, &gui::on_file_dialog_response), dialog));

  dialog->add_button("_Cancel", Gtk::ResponseType::CANCEL);
  dialog->add_button("_Open", Gtk::ResponseType::OK);

  auto filterImage = Gtk::FileFilter::create();
  filterImage->set_name("Image");

  filterImage->add_pattern("*.jpeg");
  filterImage->add_pattern("*.jpg");
  filterImage->add_pattern("*.png");

  filterImage->add_mime_type("image/jpeg");
  filterImage->add_mime_type("image/x-png");
  filterImage->add_mime_type("image/png");

  dialog->add_filter(filterImage);

  dialog->show();
}

void gui::on_folder_dialog_response(int response_id,
                                    Gtk::FileChooserDialog *dialog) {
  switch (response_id) {
  case Gtk::ResponseType::OK: {
    auto directoryName = dialog->get_file()->get_path();
    im->addImages(directoryName);
    break;
  }
  case Gtk::ResponseType::CANCEL: {
    std::cout << "Cancel clicked." << std::endl;
    break;
  }
  default: {
    std::cout << "Unexpected button clicked." << std::endl;
    break;
  }
  }
  delete dialog;
}

void gui::on_file_dialog_response(int response_id,
                                  Gtk::FileChooserDialog *dialog) {
  switch (response_id) {
  case Gtk::ResponseType::OK: {
    auto filename = dialog->get_file()->get_path();
    auto image = im->getImage(filename);
    im->addImage(image);
    break;
  }
  case Gtk::ResponseType::CANCEL: {
    break;
  }
  default: {
    std::cout << "Unexpected button clicked." << std::endl;
    break;
  }
  }
  delete dialog;
}

void gui::refresh() { imageLoader(); }

int8_t gui::on_app_activate() {
#pragma region main
  auto refBuilder = Gtk::Builder::create();
  try {
    refBuilder->add_from_file("../gui.ui");
  } catch (const Glib::FileError &ex) {
    std::cerr << "FileError: " << ex.what() << std::endl;
    return -1;
  } catch (const Glib::MarkupError &ex) {
    std::cerr << "MarkupError: " << ex.what() << std::endl;
    return -1;
  } catch (const Gtk::BuilderError &ex) {
    std::cerr << "BuilderError: " << ex.what() << std::endl;
    return -1;
  }

  mainwindow = refBuilder->get_widget<Gtk::Window>("main_window");
  imagesMatrix = refBuilder->get_widget<Gtk::Grid>("images_matrix");

  if (!mainwindow) {
    std::cerr << "Could not get the main window" << std::endl;
    return -1;
  }
  if (!imagesMatrix) {
    std::cerr << "Widget 'images_matrix' not found in gui.ui" << std::endl;
    return -1;
  }

  auto pExitBtn = refBuilder->get_widget<Gtk::Button>("exit_btn");
  auto pRefreshBtn = refBuilder->get_widget<Gtk::Button>("refresh_btn");
  auto pAddWallpaperBtn =
      refBuilder->get_widget<Gtk::Button>("add_wallpaper_btn");
  auto pAddWallpaperDirectoryBtn =
      refBuilder->get_widget<Gtk::Button>("add_wallpaper_directory_btn");

  if (pExitBtn)
    pExitBtn->signal_clicked().connect([this]() { delete mainwindow; });
  if (pRefreshBtn)
    pRefreshBtn->signal_clicked().connect([this]() { delete mainwindow; });
  if (pAddWallpaperBtn) {
    pAddWallpaperBtn->signal_clicked().connect(
        [this]() { this->addWallpaper(*mainwindow); });
  }
  if (pAddWallpaperDirectoryBtn) {
    pAddWallpaperDirectoryBtn->signal_clicked().connect(
        [this]() { this->addWallpaperDirectory(*mainwindow); });
  }

#pragma endregion

  imageLoader();
  app->add_window(*mainwindow);
  mainwindow->set_visible(true);

  return 0;
}

void gui::run(int argc, char **argv) {
  app = Gtk::Application::create("org.gtkmm.example");
  app->signal_activate().connect([this]() { gui::on_app_activate(); });
  app->run(argc, argv);
}
