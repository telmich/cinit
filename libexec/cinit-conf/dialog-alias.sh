#!/bin/sh
# Nico Schottelius
# the cLinux project
# Created: 2004-12-25
# Last-Modified:
# choose the correct dialog version

if [ -z "$DISPLAY" ]; then
   alias dialog="dialog --shadow --backtitle \"$full_version\""
else
   alias dialog="Xdialog --backtitle \"$full_version\""
fi
