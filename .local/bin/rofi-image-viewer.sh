#!/bin/bash

# Directory containing images
IMAGE_DIR="$HOME/Pictures"

# Let the user pick an image using rofi
SELECTED=$(find "$IMAGE_DIR" -type f \( -iname "*.jpg" -o -iname "*.png" -o -iname "*.jpeg" -o -iname "*.gif" \) | rofi -dmenu -i -p "Select Image")

# If an image is selected, open it in sxiv
if [[ -n "$SELECTED" ]]; then
    sxiv "$SELECTED"
fi

