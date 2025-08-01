#!/usr/bin/env bash

MUSIC_DIR="$HOME/music"

# Update MPD database
mpc update > /dev/null

# Build song list from MUSIC_DIR
songs=$(find "$MUSIC_DIR" -type f \( -iname "*.mp3" -o -iname "*.flac" -o -iname "*.wav" \) | sed "s|$MUSIC_DIR/||")

# Add control options (renamed from options → menu)
menu=$'▶ Play/Pause\n⏭ Next\n⏮ Previous\n---\n'"$songs"

# Show rofi menu
selection=$(echo "$menu" | rofi -dmenu -p "🎵 Music")

case "$selection" in
    "▶ Play/Pause")
        mpc toggle
        ;;
    "⏭ Next")
        mpc next
        ;;
    "⏮ Previous")
        mpc prev
        ;;
    "---" | "")
        exit 0
        ;;
    *)
        # Play selected song
        mpc clear
        mpc add "$selection"
        mpc play
        ;;
esac

