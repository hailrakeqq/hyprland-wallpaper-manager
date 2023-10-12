CC = clang++
BUILD_DIR = build
CORE_DIR = src/core
OUTPUT_BIN = kde-wallpaper-scheduler
SRC = src/main.cpp 
CORE_SRC = $(CORE_DIR)/imageManager.cpp $(CORE_DIR)/settings.cpp $(CORE_DIR)/wallpaperChanger.cpp $(CORE_DIR)/scheduler.cpp
all:
	mkdir -p $(BUILD_DIR)
	$(CC) -o $(BUILD_DIR)/$(OUTPUT_BIN) $(SRC) $(CORE_SRC)

clear:
	rm -rf build