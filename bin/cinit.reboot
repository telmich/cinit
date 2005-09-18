#!/bin/sh
# Nico Schottelius
# reboot system
# 2005-06-09


usage()
{
   echo "`basename $0`"
   echo "   Reboot the system:"
   exit 1
}

if [ $# -ne 0 ]; then
   usage
fi

kill -HUP 1
