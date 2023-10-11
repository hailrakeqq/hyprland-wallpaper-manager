CC = clang++
BUILD_DIR = build
OUTPUT_BIN = kde-wallpaper-scheduler
SRC = src/main.cpp
all:
	mkdir -p $(BUILD_DIR)
	$(CC) -o $(BUILD_DIR)/$(OUTPUT_BIN) $(SRC)

clear:
	rm -rf build