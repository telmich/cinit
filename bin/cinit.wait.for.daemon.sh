#!/bin/sh
# Nico Schottelius
# wait for daemon to terminate
# the pidfile is our first argument,
# the dameon the second and all others are for the daemon
# 2005-06-12 (Last Changed: 2005-06-17)

# how long to sleep before rechecking
SLEEP=5

if [ $# -lt 2 ]; then
   echo "`basename $0` <pidfile> <daemon> [daemon arguments]"
   exit 1
fi

PIDFILE=$1; shift
DAEMON=$1;  shift

# remove old pidfile
[ -e "$PIDFILE" ] && rm -f $PIDFILE

$DAEMON $@

PID=$(cat "$PIDFILE")

ISALIVE=$(ps ax | awk '{ print $1 }' | grep "^$PID\$")

while [ "$ISALIVE" ]; do
   sleep ${SLEEP}
   ISALIVE=$(ps ax | awk '{ print $1 }' | grep "^$PID\$")
done
