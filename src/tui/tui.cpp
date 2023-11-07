#include "../include/tui.h"

tui::tui(wallpaperManager& im, scheduler& s, configurator& conf)
        : im(im)
        , s(s)
        , conf(conf) {
    this->im = im;
    this->s = s;
    this->conf = conf;
}

void tui::showImages() {
    auto images = im.getImages();
    for (int i = 0; i < images.size(); i++)
        std::cout << '[' << i << ']' << " " << images[i].name << std::endl;
}

void tui::changeImage() {
    std::cout << "Enter image index: ";
    int index;
    std::cin >> index;
    if (index < im.getImagesCount()) {
        auto images = im.getImages();
        auto result = wallpaperChanger::setWallpaper(im.monitors, &images[index]);

        if (result) {
            std::cout << "Wallpaper successfully changed." << std::endl;
            return;
        }
        std::cerr << "An error occurred while setting new wallpaper." << std::endl;
        return;
    }
    std::cerr << "Index that you enter was outside of range." << std::endl;
}

void tui::setRandom() {
    std::vector<wallpaper> images = im.getImages();
    wallpaper currentImg = s.getCurrentImage();

checkIsCurrentImageNotEqualRandomImage:
    wallpaper imageToSet = utils::getRandomItem(images);

    if (currentImg.fullPath == imageToSet.fullPath) {
        goto checkIsCurrentImageNotEqualRandomImage;
    }

    wallpaperChanger::setWallpaper(im.monitors, &imageToSet);
    s.setCurrentImage(&imageToSet);
}

void tui::addImagesToImageManager() {
    std::cout << "Enter path to wallpaper directory: ";
    std::string path;
    getline(std::cin, path);

    im.addImages(path);
    std::cout << "Image was successfully added to image manager" << std::endl;
}

void tui::addImageToPlaylist() {
    std::cout << "Enter path to image: ";
    std::string imagePath;
    getline(std::cin, imagePath);

    if (!imagePath.empty()) {
        auto img = im.getWallpaper(imagePath);
        s.addImageToPlaylist(img);
        conf.saveConfig();
    }
}

void tui::addImagesToPlaylist() {
    std::cout << "Enter path to directory: " << std::endl;
    std::string imagesDirectoryPath;
    getline(std::cin, imagesDirectoryPath);

    if (!imagesDirectoryPath.empty()) {
        auto images = im.getImages(imagesDirectoryPath);
        for (auto image : images)
            s.addImageToPlaylist(&image);

        conf.saveConfig();
    }
}

void tui::removeImageFromPlaylist() {
    int index;
    std::cout << "Enter image index to delete: ";
    std::cin >> index;

    if (index > s.playlistSize()) {
        std::cout << "Index is greater than count images in playlist" << std::endl;
        return;
    }

    s.removeImageFromPlaylist(index);
    conf.saveConfig();
}

void tui::removeImageFromImageManager() {
    std::cout << "Enter image index to delete: ";
    int index;
    std::cin >> index;

    if (index > im.getImagesCount()) {
        std::cout << "Index is greater than count images in image manager"
                  << std::endl;
        return;
    }

    im.deleteWallpaper(index);
    conf.saveConfig();
    std::cout << "Image was successfully deleted" << std::endl;
}

void tui::playlistSettings() {
    int option;
    do {
        std::cout << "Playlist settings:" << std::endl;
        std::cout << "1. Add image to playlist" << std::endl;
        std::cout << "2. Add images directory to playlist" << std::endl;
        std::cout << "3. Remove Image from playlist" << std::endl;
        std::cout << "4. Back" << std::endl;
        std::cout << "Choose option: ";

        std::cin >> option;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (option) {
            case 1:
                addImageToPlaylist();
                break;
            case 2:
                addImagesToPlaylist();
                break;
            case 3:
                removeImageFromPlaylist();
                break;
            default:
                std::cout << "Incorrect choose." << std::endl;
                break;
        }
    } while (option != 4);
}

void tui::showPlaylist() {
    for (auto image : s.getPlaylist())
        image.printFileDetails();
}

void tui::changeInterval() {
    std::cout << "Enter new interval(example: \"2.30\" - 2 hour 30 minutes.): "
              << std::endl;
    std::string newInterval;
    std::cin >> newInterval;
    s.changeInterval(newInterval);
}

void tui::changeDisplay() {
    std::cout << "Enter monitor(s) on which you want set wallpaper(example "
                 "\"DP-1, DP-2\"): ";
    std::string monitorInput;
    std::getline(std::cin, monitorInput);
    if (!monitorInput.empty()) {
        im.monitors = monitorInput;
        conf.updateMonitors(monitorInput);
    }
}

void tui::schedulerMenu() {
    int choice;
    do {
        std::cout << "Scheduler Menu:" << std::endl;
        std::cout << "1. start" << std::endl;
        std::cout << "2. stop" << std::endl;
        std::cout << "3. show playlist" << std::endl;
        if (s.isRandomImage())
            std::cout << "4. set playlist image?" << std::endl;
        else
            std::cout << "4. set random image?" << std::endl;
        std::cout << "5. playlist settings" << std::endl;
        std::cout << "6. settings" << std::endl;
        std::cout << "7. Exit" << std::endl;
        std::cout << "Choose option: ";

        std::cin >> choice;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                s.start();
                break;
            case 2:
                s.stop();
                break;
            case 3:
                showPlaylist();
                break;
            case 4:
                s.setRandomImage();
                break;
            case 5:
                playlistSettings();
                break;
            case 6:
                changeInterval();
                break;
            case 7:
                std::cout << "Exit..." << std::endl;
                break;
            default:
                std::cout << "Incorrect choose." << std::endl;
                break;
        }
    } while (choice != 7);
}

void tui::renderMenu() {
    int choice;
    do {
        std::cout << "Menu:" << std::endl;
        std::cout << "1. show images" << std::endl;
        std::cout << "2. add images directory" << std::endl;
        std::cout << "3. remove image directory" << std::endl;
        std::cout << "4. set random wallpaper" << std::endl;
        std::cout << "5. set wallpaper" << std::endl;
        std::cout << "6. scheduler" << std::endl;
        std::cout << "7. settings" << std::endl;
        std::cout << "8. Exit" << std::endl;
        std::cout << "Choose option: ";

        std::cin >> choice;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                showImages();
                break;
            case 2:
                addImagesToImageManager();
                break;
            case 3:
                removeImageFromImageManager();
                break;
            case 4:
                setRandom();
                break;
            case 5:
                changeImage();
                break;
            case 6:
                schedulerMenu();
                break;
            case 7:
                changeDisplay();
                break;
            case 8:
                std::cout << "Exit." << std::endl;
                break;
            default:
                std::cout << "Incorrect choose." << std::endl;
                break;
        }
    } while (choice != 8);
}