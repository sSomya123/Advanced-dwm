#!/bin/bash

# Rofi Power Menu
chosen=$(echo -e " Lock\n Logout\n Reboot\n Shutdown\n Suspend" | rofi -dmenu -i -p "Power" -theme-str 'window {width: 20%;}')

case "$chosen" in
    " Lock") 
        slock 
        ;;
    " Logout") 
        pkill -KILL -u $USER 
        ;;
    " Reboot") 
        systemctl reboot 
        ;;
    " Shutdown") 
        systemctl shutdown 
        ;;
    " Suspend") 
        systemctl suspend 
        ;;
esac

