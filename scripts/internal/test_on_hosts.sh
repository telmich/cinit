hosts="penrose.bsdprojects.net"

for host in $hosts; do
   echo "$1 on $host"
   "$1" "$host"
done
