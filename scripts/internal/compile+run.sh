#!/bin/sh
# yah - yet another hack

host="$1"

hier=$(dirname $0)

$hier/compile_test.sh "$1"

if [ $? -ne 0 ]; then
   echo "aborting, did not compile on $1"
   exit 1
fi

ssh "${host}" './cinit/src/cinit & (sleep 30; kill -9 $(pgrep cinit))'
