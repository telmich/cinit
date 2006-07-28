#!/bin/sh
# Nico Schottelius
# cinit: setups symlinks for the os
# 


DDIR=$(dirname $0)/../src/os/
OSCONFIG=$(dirname $0)/../conf/os

OS=$(head -n 1 "$OSCONFIG")

echo "Making links for $OS ..."

cd "$DDIR"

rm -f current
ln -sf "$OS" current
