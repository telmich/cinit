#!/bin/sh
# Nico Schottelius
# 2007-09-27: Test cmd
#


echo "Testing cmd..."
sudo /sbin/cmd -s /etc/cinit/svc/init
sudo /sbin/cmd -p /etc/cinit/svc/init
sudo /sbin/cmd -v
sudo /sbin/cmd -V
