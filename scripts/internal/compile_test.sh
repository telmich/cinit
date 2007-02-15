host="$1"

rsync --exclude .git -av ./ "${host}:cinit"
ssh "${host}" "./cinit/scripts/internal/compile_local.sh"
