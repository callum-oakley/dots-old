#!/bin/sh

xsetroot -solid '#57877B'

IN="eDP1"
EXT="HDMI2"

if (xrandr | grep "$EXT disconnected"); then
    internal-monitor
else
    external-monitor
fi

xbindkeys
2bwm &

slow-trackball
flux

exec urxvt
