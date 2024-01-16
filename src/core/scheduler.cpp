#include "../../include/scheduler.h"

scheduler::scheduler(configurator* conf, wallpaperManager* wm) {
    auto config = conf->getConfig();
    std::ifstream jsonFile("config.json");
    if (!jsonFile.is_open()) {
        std::cerr << "Failed to open config file." << std::endl;
        return;
    }

    json jsonData;
    jsonFile >> jsonData;
    jsonFile.close();

    if (jsonData.contains("scheduler") && !jsonData["scheduler"].empty()) {
        json scheduler = jsonData["scheduler"];
        json playlist = scheduler["playlist"];
        randomImage = scheduler["isRandomImage"];
        this->interval = scheduler["interval"];

        for (auto item : playlist) {
            wallpaper img;

            img.fullPath = item["fullPath"];
            img.name = item["name"];
            img.size = item["size"];
            img.lastModifiedTimet = item["lastModifiedTime"];

            scheduler::playlist.push_back(img);
        }
    }

    currentImageIndex = 0;
    this->wm = wm;
    this->conf = conf;
    isSchedulerRun = false;

    auto schedulerJson = toJson();
    conf->updateScheduler(schedulerJson);
}

scheduler::scheduler(std::string interval, configurator* conf, wallpaperManager* wm) {
    int intervalInMinutes = utils::getImageIntervalTimeInMinutes(interval);
    if (intervalInMinutes == -1)
        this->interval = 0;
    else
        this->interval = intervalInMinutes;

    currentImageIndex = 0;
    this->wm = wm;
    isSchedulerRun = false;
    randomImage = true;
}

json scheduler::toJson() {
    json jsonObject;
    jsonObject["isRandomImage"] = randomImage;
    jsonObject["interval"] = interval;
    json playlistArray;

    for (auto img : playlist) {
        json imageJson;

        imageJson["name"] = img.name;
        imageJson["fullPath"] = img.fullPath;
        imageJson["size"] = img.size;
        imageJson["lastModifiedTime"] = img.lastModifiedTimet;

        playlistArray.push_back(imageJson);
    }
    jsonObject["playlist"] = playlistArray;

    return jsonObject;
}

wallpaper scheduler::getCurrentImage() { return currentImage; }

void scheduler::setCurrentImage(wallpaper* img) { currentImage = *img; }

void scheduler::addImageToPlaylist(wallpaper* img) {
    playlist.push_back(*img);
    conf->addWallpaper(img, PLAYLIST);
}

void scheduler::removeImageFromPlaylist(wallpaper* img) {
    for (uint i = 0; i < playlist.size(); i++) {
        if (playlist[i].fullPath == img->fullPath) {
            playlist.erase(playlist.begin() + i);
            conf->removeWallpaper(img, PLAYLIST);
        }
    }
}

void scheduler::removeImageFromPlaylist(uint index) {
    if (index > playlist.size()) {
        std::cerr << "Index outside of array size" << std::endl;
        return;
    }

    playlist.erase(playlist.begin() + index);
    conf->removeWallpaper(index, PLAYLIST);
}

void scheduler::start() {
    if (isSchedulerRun) {
        std::cout << "Scheduler already run." << std::endl;
        return;
    }

    isSchedulerRun = true;

    while (isSchedulerRun == true) {
        scheduleImage();
        std::this_thread::sleep_for(std::chrono::minutes(interval));
    }
}

int scheduler::playlistSize() { return playlist.size(); }

void scheduler::scheduleImage() {
    wallpaper imageToSet;

    if (randomImage == true) {
    checkIsCurrentImageNotEqualRandomImage:
        imageToSet = utils::getRandomItem(wm->getImages());
        if (currentImage.fullPath == imageToSet.fullPath)
            goto checkIsCurrentImageNotEqualRandomImage;
    } else {
        if (playlist.empty()) {
            std::cout << "Playlist is empty." << std::endl;
            return;
        }
        if (currentImageIndex == playlist.size())
            currentImageIndex = 0;

        imageToSet = playlist[currentImageIndex];
        currentImageIndex++;
    }

    auto monitors = conf->getMonitors();
    wallpaperChanger::setWallpaper(monitors, &imageToSet);
    currentImage = imageToSet;
}

void scheduler::stop() { isSchedulerRun = false; }

bool scheduler::isRandomImage() { return randomImage; }

void scheduler::setRandomImage() {
    randomImage == true ? randomImage = false : randomImage = true;
    conf->setImageSchedulerType(randomImage);
}

void scheduler::changeInterval(std::string interval) {
    int intervalInMinutes = utils::getImageIntervalTimeInMinutes(interval);
    intervalInMinutes == -1 ? this->interval = 0
                            : this->interval = intervalInMinutes;

    auto jsonSchedler = this->toJson();
    conf->updateScheduler(jsonSchedler);
    conf->saveConfig();
}

std::vector<wallpaper> scheduler::getPlaylist() { return playlist; }
