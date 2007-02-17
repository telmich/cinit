#!/bin/sh

src="$(dirname $0)/../../"
src_abs=$(cd "$src" && pwd -P)

for commit in $( git log --pretty=short | awk '/^commit/ { print $2 }'); do
   set -e
   cd "$src_abs"
   temp=$(mktemp -d /tmp/cinit.XXXXXXXXXX)
   git-archive --format=tar "$commit" | ( cd "$temp"; tar x )
   cd "${temp}/src"
   set +e
   make clean && make cinit && ./cinit
   if [ "$?" -eq 0 ]; then
      echo "Commit $commit is ok"
      exit 0
   fi
   echo "Broken $commit"
   sleep 1
   set -e
   rm -rf "$temp"
done

exit 1
