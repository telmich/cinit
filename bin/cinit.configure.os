#!/bin/sh
# Nico Schottelius
# cinit: setups symlinks for the os
# 


DDIR=$(dirname $0)/../os/
OSCONFIG=$(dirname $0)/../conf/os

OS=$(head -n 1 "$OSCONFIG")

echo "Making links for $OS ..."

cd "$DDIR"

ln -sf "$OS" current
