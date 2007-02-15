dir=$(dirname $0)

sys=$(uname -s)
sys_small=$(echo $sys |  tr '[A-Z]' '[a-z]')

case $(uname -s) in
   NetBSD)
      make=gmake
      ;;
esac

cd "${dir}/../../src"
$make clean
echo $sys_small > conf/os
./bin/cinit.configure.os
$make cinit