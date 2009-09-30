#!/bin/sh

ROOT=$(dirname $0)/Debian-3.0r0.ext2

linux ubd0=$ROOT init=/bin/sh "$@"
