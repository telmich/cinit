#!/bin/sh
# yah

hosts="penrose.bsdprojects.net"

set -e

for host in $hosts; do
   echo "$1 on $host"
   "$1" "$host"
done
