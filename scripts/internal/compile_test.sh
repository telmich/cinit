#!/bin/sh
# yah - yet another hack

host="$1"

rsync --exclude .git --exclude \*.o -av ./ "${host}:cinit"
ssh "${host}" "./cinit/scripts/internal/compile_local.sh"
