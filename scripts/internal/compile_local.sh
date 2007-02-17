# just a hack

dir=$(dirname $0)

sys=$(uname -s)
sys_small=$(echo $sys |  tr '[A-Z]' '[a-z]')

case $(uname -s) in
   NetBSD|OpenBSD)
      make=gmake
      ;;
   *)
      make=make
      ;;
esac

cd "${dir}/../../"
echo $sys_small > conf/os
# automatically called by make..
#./bin/cinit.configure.os

cd "src"
$make clean
$make cinit
