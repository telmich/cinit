#!/bin/sh

ROOT=$(dirname $0)/../root/Debian-3.0r0.ext2

qemu  -hda "$ROOT" "$@"
