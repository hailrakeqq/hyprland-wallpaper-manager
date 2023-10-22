#include "../include/utils.h"

namespace utils
{
    std::string getFileName(std::string filePath) {
        std::filesystem::path path(filePath);
        return path.filename().string();
    }

    int getImageIntervalTimeInMinutes(std::string interval){
        int hours, minutes;
        size_t dotPos = interval.find('.');
        if (dotPos != std::string::npos) {
            hours = std::stoi(interval.substr(0, dotPos));
            minutes = std::stoi(interval.substr(dotPos + 1));
        } else {
            std::cout << "Uncorrect time format." << std::endl;
            return -1;
        }

        int totalMinutes = hours * 60 + minutes;
        return totalMinutes;
    }

    long getFileSize(std::string filePath){
        std::ifstream file(filePath, std::ios::binary);
        if(!file){
            std::cerr << "Can't open file." << std::endl;
            return 1;
        }

        file.seekg(0, std::ios::end);
        long fileSize = (long)file.tellg();
        file.close();
        return fileSize;
    }

    image *getRandomImage(std::vector<image> &images){
        int randomIndex = rand() % images.size();

        auto randomImage = images[randomIndex];

        return &randomImage;
    }

    std::vector<image>::iterator getItemIndexInVector(std::vector<image> & vec, image *img){
        for (auto i = vec.begin(); i != vec.end(); ++i) {
            if (i->fullPath == img->fullPath) 
                return i;
        }
        return vec.end();
    }
}
