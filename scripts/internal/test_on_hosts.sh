#!/bin/sh
# yah

hosts="penrose.bsdprojects.net jiffies.forkbomb.ch ddna044.netstream.ch"

set -e

for host in $hosts; do
   echo "$1 on $host"
   "$1" "$host" | sed "s/^/${host}: /"
   echo "==> Finished $host"
done
