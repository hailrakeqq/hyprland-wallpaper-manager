#include "../include/utils.h"

namespace utils {
    std::string getFileName(std::string filePath) {
        std::filesystem::path path(filePath);
        return path.filename().string();
    }

    std::string getPrimaryMonitorName() {
        char buffer[128];
        std::string result = "";

        FILE* pipe = popen("xrandr --listmonitors", "r");
        if (!pipe)
            throw std::runtime_error("popen() failed!");

        try {
            while (fgets(buffer, sizeof(buffer), pipe) != NULL)
                result += buffer;
        } catch (...) {
            pclose(pipe);
            throw;
        }

        pclose(pipe);

        std::istringstream iss(result);
        std::vector<std::string> tokens;

        while (iss >> result)
            tokens.push_back(result);

        if (!tokens.empty())
            result = tokens.back();

        return result;
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

    wallpaper getRandomItem(const std::vector<wallpaper>& arr) {
        if (arr.empty())
            throw std::invalid_argument("The array is empty");

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<size_t> distribution(0, arr.size() - 1);

        size_t randomIndex = distribution(gen);
        return arr[randomIndex];
    }

    std::vector<wallpaper>::iterator getItemIndexInVector(std::vector<wallpaper>& vec,
        wallpaper* img) {
        for (auto i = vec.begin(); i != vec.end(); ++i) {
            if (i->fullPath == img->fullPath)
                return i;
        }
        return vec.end();
    }
} // namespace utils
