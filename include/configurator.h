#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include <string>
#include <fstream>
//TODO: add json lib

#include "../include/imageManager.h"

class configurator {
public:
    void initializeConfig(std::string &configFilePath);
    imageManager *initializeImageManager(std::string &configFilePath);

private:
    std::string configPath;
};
#endif // CONFIGURATOR_H