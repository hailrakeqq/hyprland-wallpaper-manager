#include "../include/cmdUI.h"

cmdUI::cmdUI(imageManager& im, scheduler &s, configurator& conf) : im(im), s(s), conf(conf){
    this->im = im;
    this->s = s;
    this->conf = conf;
}

void cmdUI::showImages()
{
    auto images = im.getImages();
    for (int i = 0; i < images.size(); i++)
        std::cout << '[' << i << ']' << " " << images[i].name << std::endl;
}

void cmdUI::changeImage(){
    std::cout << "Enter image index: ";
    int index;
    std::cin >> index;
    if(index < im.getImagesCount()){
        auto images = im.getImages();
        auto result = wallpaperChanger::setWallpaper(im.monitors, &images[index]);

        if(result){
            std::cout << "Wallpaper successfully changed." << std::endl;
            return;
        }
        std::cerr << "An error occurred while setting new wallpaper." << std::endl;
        return;
    }
    std::cerr << "Index that you enter was outside of range." << std::endl;
}

void cmdUI::setRandom(){
    std::vector<image> images = im.getImages();
    image currentImg = s.getCurrentImage();

    checkIsCurrentImageNotEqualRandomImage:
    image imageToSet = utils::getRandomItem(images);
   
    if(currentImg.fullPath == imageToSet.fullPath){
        goto checkIsCurrentImageNotEqualRandomImage;
    }
    

    wallpaperChanger::setWallpaper(im.monitors, &imageToSet);
    s.setCurrentImage(&imageToSet);
}

void cmdUI::addImagesToImageManager(){
    std::cout << "Enter path to wallpaper directory: ";
    std::string path;
    getline(std::cin, path);
    
    im.addImages(path);
}

void cmdUI::addImageToPlaylist(){
    std::string imagePath;
    getline(std::cin, imagePath);

    if(!imagePath.empty()){
        auto img = im.getImage(imagePath);
        s.addImageToPlaylist(img);
    }
}

void cmdUI::addImagesToPlaylist(){
    std::cout << "Enter path to directory: " << std::endl;
    std::string imagesDirectoryPath;
    getline(std::cin, imagesDirectoryPath);

    if(!imagesDirectoryPath.empty()){
        auto images = im.getImages(imagesDirectoryPath);
        for(auto image: images)
            s.addImageToPlaylist(&image);
    }
}

void cmdUI::removeImageFromPlaylist(){
    uint index;
    std::cout << "Enter image index to delete: " << std::endl;
    std::cin >> index;

    if(index > s.playlistSize()){
        std::cout << "Index is greater than count images in playlist" << std::endl;
        return;
    }

    s.removeImageFromPlaylist(index);
}

void cmdUI::playlistSettings(){
    uint8_t option;
    do {
        std::cout << "Playlist settings:" << std::endl;
        std::cout << "1. Add image to playlist" << std::endl;
        std::cout << "2. Add images directory to playlist" << std::endl;
        std::cout << "3. Remove Image from playlist" << std::endl;
        std::cout << "4. Back" << std::endl;
        std::cout << "Choose option: ";

        std::cin >> option;
        static_cast<uint8_t>(option);
        switch (option)
        {
            case 1:
                addImageToPlaylist();
                break;
            case 2:
                addImagesToPlaylist();
                break;
            case 3:
                removeImageFromPlaylist();
                break;
            case 4:
                break;
            default:
                std::cout << "Incorrect choose." << std::endl;
                break;
        }
    } while (option != 4);
}

void cmdUI::showPlaylist(){
    for(auto image : s.getPlaylist())
        image.printFileDetails();
}

void cmdUI::changeInterval(){
    std::cout << "Enter new interval(example: \"2.30\" - 2 hour 30 minutes.): " << std::endl;
    std::string newInterval;
    std::cin >> newInterval;
    s.changeInterval(newInterval);
}

void cmdUI::changeDisplay(){
    std::cout << "Enter monitor(s) on which you want set wallpaper(example \"DP-1, DP-2\"): ";
    std::string monitorInput;
    std::getline(std::cin, monitorInput);
    if(!monitorInput.empty()){
        im.monitors = monitorInput;
        conf.updateMonitors(monitorInput);
    }
}

void cmdUI::schedulerMenu(){
    int choice;
    do {
        std::cout << "Scheduler Menu:" << std::endl;
        std::cout << "1. start" << std::endl;
        std::cout << "2. stop" << std::endl;
        std::cout << "3. show playlist" << std::endl;        
        std::cout << "4. playlist settings" << std::endl;        
        std::cout << "5. settings" << std::endl;
        std::cout << "6. Exit" << std::endl;
        std::cout << "Choose option: ";
        
        std::cin >> choice;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice)
        {
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
            playlistSettings();
            break;
        case 5:
            changeInterval();
            break;
        case 6:
            std::cout << "Exit..." << std::endl;
            break;
        default:
            std::cout << "Incorrect choose." << std::endl;
            break;
        }
    } while (choice != 6);
}

void cmdUI::renderMenu(){
    int choice;
    do {
        std::cout << "Menu:" << std::endl;
        std::cout << "1. show images" << std::endl;
        std::cout << "2. add image directory" << std::endl;
        std::cout << "3. set random wallpaper" << std::endl;
        std::cout << "4. set wallpaper" << std::endl;
        std::cout << "5. scheduler" << std::endl;        
        std::cout << "6. settings" << std::endl;
        std::cout << "7. Exit" << std::endl;
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
                setRandom();
                break;
            case 4:
                changeImage();
                break;
            case 5:
                schedulerMenu();
                break;
            case 6:
                changeDisplay();
                break;
            case 7:
                std::cout << "Exit." << std::endl;
                break;
            default:
                std::cout << "Incorrect choose." << std::endl;
                break;
        }
    } while (choice != 7);
}