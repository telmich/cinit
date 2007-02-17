hier=$(dirname $0)

set -e
${hier}/../cinit.install.standard.dirs
cat > /etc/cinit/svc/init/on << eof
#!/bin/sh
echo test1
sleep 4
echo test2 - \$@
eof
chmod 0755 /etc/cinit/svc/init/on

cat > /etc/cinit/svc/init/on.params << eof
es
scheint
zu
gehen
eof
