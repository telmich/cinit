#!/bin/sh
# Nico Schottelius
# cinit: setups symlinks for the os
# 

DDIR=$(dirname $0)/../../src/os
DFILE="$DDIR/current"
OSCONFIG=$(dirname $0)/../../conf/os

OS=$(head -n 1 "$OSCONFIG")

echo "Configure: OS:  Binaries are created for $OS ..."

rm -f "${DFILE}"
ln -sf "${OS}" "${DFILE}"
