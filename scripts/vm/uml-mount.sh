SDIR=$(dirname $0)
DDIR=$(dirname $0)/root
sudo mount "$SDIR/Debian-3.0r0.ext2" "$DDIR" -o loop,acl,sync
