#!/bin/sh
# yah - yet another hack

host="$1"
what=$(dirname $0)/../../

rsync --exclude .git --exclude \*.o -av "${what}" "${host}:cinit"
ssh "${host}" "./cinit/scripts/internal/compile_local.sh"
