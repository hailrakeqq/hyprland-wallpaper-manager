#include "../include/cmdUI.h"

//TODO: дописати ось цю менюшку

cmdUI::cmdUI(imageManager& im, scheduler &s) : im(im), s(s){
    this->im = im;
    this->s = s;
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
    image *imageToSet = im.getRandomImage();
    image *currentImg = s.getCurrentImage();
    
    if (currentImg != nullptr) {
        checkIsCurrentImageNotEqualRandomImage:
        if(currentImg->fullPath == imageToSet->fullPath){
            imageToSet = im.getRandomImage();
            goto checkIsCurrentImageNotEqualRandomImage;
        }
    }

    wallpaperChanger::setWallpaper(im.monitors, imageToSet);
    s.setCurrentImage(imageToSet);
}

void cmdUI::addImages(){
    std::cout << "Enter path to wallpaper directory: ";
    std::string path;
    getline(std::cin, path);
    
    im.addImages(path);
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

void cmdUI::schedulerMenu(){
    int choice;
    do {
        std::cout << "Scheduler Menu:" << std::endl;
        std::cout << "1. start" << std::endl;
        std::cout << "2. stop" << std::endl;
        std::cout << "3. show playlist" << std::endl;        
        std::cout << "4. settings" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "Choose option (1/2/3/4/5): ";
        
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
            changeInterval();
            break;
        case 5:
            std::cout << "Exit..." << std::endl;
            break;
        default:
            std::cout << "Incorrect choose." << std::endl;
            break;
        }
    } while (choice != 5);
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
                addImages();
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
                std::cout << "Settings" << std::endl;
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