#!/bin/bash

sudo rm /usr/local/bin/hyprland-wallpaper-manager
sudo rm -rf /usr/share/hyprland-wallpaper-manager/
sudo rm /usr/share/applications/hyprland-wallpaper-manager.desktop

if [ $? -eq 0 ]; then
    echo "Uninstallation completed successfully."
else 
    echo "An error occurred during uninstallation."
fi
