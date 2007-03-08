#!/bin/sh
# yah - yet another hack

if [ ! "$1" ]; then
   echo "HOSTNAME"
   exit 23
fi

host="$1"

hier=$(dirname $0)

$hier/compile_test.sh "$host"

if [ $? -ne 0 ]; then
   echo "aborting, did not compile on $1"
   exit 1
fi

ssh "${host}" './cinit/src/cinit & (sleep 30; kill -9 $(pgrep cinit))'
