#
# 2008      Nico Schottelius (nico-cconf at schottelius.org)
# 
# This file is part of cconf.
#
# cconf is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# cconf is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with cconf. If not, see <http://www.gnu.org/licenses/>.
#
# Sample Makefile for use with cconf
#

name=cinit-conf
release=0.1

host=home.schottelius.org
dir=www/org/schottelius/unix/www/cinit-conf
archives=archives
bs=browse_source

all:
	echo "No enduser targets. Please read README."

release: ../$(name)-$(release).tar.gz  \
		../$(name)-$(release).tar.bz2 ../$(name)-$(release).tar.lzma
	scp $^ $(host):$(dir)/$(archives)
	ssh $(host) "cd $(dir)/$(bs); tar xvfj ../$(archives)/$(name)-$(release).tar.bz2"
	ssh $(host) "find $(dir) -type d -exec chmod 0755 {} \; ; find $(dir) -type f -exec chmod 0644 {} \;"

../$(name)-$(release).tar:
	# no exclude possible of .git with pax it seems
	#pax -w -x ustar -s '/^\./$(name)-$(release)/' -w . -f $@
	pax -w -x ustar -s ';^;$(name)-$(release)/;' -f $@ -w *

../$(name)-$(release).tar.gz:  ../$(name)-$(release).tar
	gzip -9 -c $^ > $@

../$(name)-$(release).tar.bz2:  ../$(name)-$(release).tar
	bzip2 -9 -c $^ > $@

../$(name)-$(release).tar.lzma:  ../$(name)-$(release).tar
	lzma -9 -c $^ > $@
