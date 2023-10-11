#include <fstream>
#include <sstream>
#include <vector>

std::vector<std::string> split (const std::string &s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss (s);
    std::string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}

std::string getFileName(std::string filePath) {
    return split(filePath, '/').back();
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
