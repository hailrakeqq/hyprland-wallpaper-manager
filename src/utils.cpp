#include "../include/utils.h"

namespace utils {
    std::string getFileName(std::string filePath) {
        std::filesystem::path path(filePath);
        return path.filename().string();
    }

    int getImageIntervalTimeInMinutes(std::string interval) {
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

    long getFileSize(std::string filePath) {
        std::ifstream file(filePath, std::ios::binary);
        if (!file) {
            std::cerr << "Can't open file." << std::endl;
            return 1;
        }

        file.seekg(0, std::ios::end);
        long fileSize = (long)file.tellg();
        file.close();
        return fileSize;
    }

    image getRandomItem(const std::vector<image>& arr) {
        if (arr.empty())
            throw std::invalid_argument("The array is empty");

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<size_t> distribution(0, arr.size() - 1);

        size_t randomIndex = distribution(gen);
        return arr[randomIndex];
    }

    std::vector<image>::iterator getItemIndexInVector(std::vector<image>& vec,
        image* img) {
        for (auto i = vec.begin(); i != vec.end(); ++i) {
            if (i->fullPath == img->fullPath)
                return i;
        }
        return vec.end();
    }
} // namespace utils
