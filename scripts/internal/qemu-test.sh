#!/bin/sh
# Nico Schottelius
# 2007-09-03: For testing cinit in qemu
#

emud="${HOME}/emu"
img="${emud}/debian-hd.img"
ddir="${emud}/mount"
loop=/dev/loop1
fsck="/sbin/fsck.jfs"

# my jfs is on the first partition, 512*63 bytes offset
offset="32256"

set -e
set -x
sudo losetup -o "${offset}" "${loop}" "${img}"
sudo "${fsck}" "${loop}"
sudo mount "${loop}" "${ddir}"

sudo umount "${loop}"
sudo losetup -d "${loop}"
