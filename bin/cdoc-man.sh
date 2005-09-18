#!/bin/sh
#
# Nico Schottelius <nico-linux@schottelius.org>
# Date: 21-Aug-2005
# Last Modified: -
#

set -e

[ $# -ne 1 ] && exit 23

SRC=$1

cd "$SRC"

#
# Title heading
#
echo .TH $(cat "meta/name" "meta/man_section" "meta/date")

#
# Name
#
echo .SH NAME
echo $(cat meta/name) - $(cat meta/short_description)

#
# Synopsis
#
echo .SH SYNOPSIS
echo $(cat path) $(cat parameters)

#
# description
#
echo .SH DESCRIPTION
echo $(cat long_description)

#
# availability
#
for section in availability examples "see also" author; do
   if [ -f "$section" ]; then
      echo .SH $section | tr '[a-z]' '[A-Z]'
      cat "$section"
   fi
done

#
# files
#
if [ -f files ]; then
   echo .SH FILES
   cat files | sed 's/\(.*\)/.IP "\1" /'
fi

exit 0
