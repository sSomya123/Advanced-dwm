#!/bin/bash

# Directory containing wallpapers
WALLPAPER_DIR="$HOME/Pictures/Wallpapers"

# Let the user pick a wallpaper using rofi
SELECTED=$(find "$WALLPAPER_DIR" -type f \( -iname "*.jpg" -o -iname "*.png" -o -iname "*.jpeg" \) | rofi -dmenu -i -p "Select Wallpaper")

# If a wallpaper is selected, set it with feh
if [[ -n "$SELECTED" ]]; then
    feh --bg-fill "$SELECTED"
fi

