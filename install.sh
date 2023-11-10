#!/bin/bash

rm -rf build
mkdir -p build
git clone https://github.com/nlohmann/json/
cd build 
cmake -DCMAKE_BUILD_TYPE=Release -DDEBUG=OFF ..
make

if [ $? -ne 0 ]; then
    echo "An error occurred during compilation."
    exit 1
fi

sudo cp hyprland-wallpaper-manager /usr/local/bin/
sudo chmod +x /usr/local/bin/hyprland-wallpaper-manager

sudo mkdir /usr/share/hyprland-wallpaper-manager/
sudo cp -r ui /usr/share/hyprland-wallpaper-manager/ 
mkdir ~/.config/hyprland-wallpaper-manager/

echo "[Desktop Entry]
Name=Hyprland Wallpaper Manager
Exec=/usr/local/bin/hyprland-wallpaper-manager
Type=Application
Categories=Utility;" | sudo tee /usr/share/applications/hyprland-wallpaper-manager.desktop

if [ $? -eq 0 ]; then
    echo "Installation completed successfully."
else
    echo "An error occurred during installation."
fi