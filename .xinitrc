#!/bin/bash
xrandr --output Virtual-1 --mode 1920x1080
~/.fehbg
dunst &
slstatus &
#exec dwmblocks &:w
xss-lock -- /run/wrappers/bin/slock &
clipmenud &
xclip &
picom &
export CM_LAUNCHER="rofi"
exec dwm
