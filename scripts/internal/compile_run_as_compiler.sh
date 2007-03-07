what=$(dirname $0)/../../
what_real=$(cd "$what" && pwd -P)
dest=~compiler/cinit-test

set -e
sudo rsync -av "${what_real}/" "$dest"
sudo chown -R compiler "$dest"
sudo -u compiler "${dest}/scripts/internal/compile_local.sh"
sudo -u compiler "${dest}/src/cinit"
