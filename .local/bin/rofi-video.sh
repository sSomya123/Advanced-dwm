#!/usr/bin/env bash

VIDEO_DIR="$HOME/Videos"

# Find all video files
video=$(find "$VIDEO_DIR" -type f \( -iname "*.mp4" -o -iname "*.mkv" -o -iname "*.avi" -o -iname "*.mov" \) \
  | rofi -dmenu -i -p "🎬 Select Video" \
  -preview 'mediainfo {}' \
  -preview-window down:20%)

# If selection is not empty, play it
[ -n "$video" ] && mpv "$video"

