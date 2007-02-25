what=$(dirname $0)/../../
what_real=$(cd "$what" && pwd -P)
dest=~compiler/cinit-test

rsync -av "${what_real}/" "$dest"
chown -R compiler "$dest"
su - compiler -c "cd $dest && make -C src all && ./src/cinit"
