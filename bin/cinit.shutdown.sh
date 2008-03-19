#!/bin/sh
# Nico Schottelius
# shutdown system
# TODO: use ccontrol!
# 2005-05-24 (Last changed: 2005-06-18)


usage()
{
   echo "`basename $0` -[ohr]"
   echo "   Shutdown the system:"
   echo "   -p|--power-off:   Power off"
   echo "   -h|--halt:        Halt"
   echo "   -r|--reboot:      Reboot"
   echo "   -s|--rescue:      Rescue mode"
   echo "   "
   exit 1
}

if [ $# -ne 1 ]; then
   usage
fi

case $1 in
   -r|--reboot)      kill -HUP  1 ;;
   -p|--power-off)   kill -TERM 1 ;;
   -h|--halt)        kill -USR1 1 ;;
   -s|--rescue)      kill -USR2 1 ;;
    *)               usage ;;
esac
