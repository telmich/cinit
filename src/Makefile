#
# 2008      Nico Schottelius (nico-cinit at schottelius.org)
#
# This file is part of cinit.

# cinit is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# cinit is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with cinit.  If not, see <http://www.gnu.org/licenses/>.

#
# Don't edit Makefiles, use conf/* for configuration.
#

################################################################################
#
# Build tools / locations
#

CC=../tmpbin/cc
CFLAGS=
LD=../tmpbin/ld
LDFLAGS=
STRIP=../tmpbin/strip
SBIN=../sbin
DESTDIR=
#DESTDIR=/home/user/nico/emu/dst

################################################################################
#
# All objects / binaries
#    depend on headers. More or less. FIXME: use gcc -M
#
BIN=cinit.halt cinit.poweroff cinit.reboot cmd
CINIT=cinit
ALLBIN=${BIN} ${CINIT}

# headers
CONFIG_H=include/config.h
CINIT_HEADERS=${shell cat include/listing}

# objects
CINIT_OBJ=${shell cat object_lists/cinit}
HALTKILL_OBJ=${shell cat object_lists/halt.kill}
POWEROFFKILL_OBJ=${shell cat object_lists/poweroff.kill}
REBOOTKILL_OBJ=${shell cat object_lists/reboot.kill}
CMD_OBJ=${shell cat object_lists/cmd}

#
# All objects
#
OBJ=${CINIT_OBJ} ${HALTKILL_OBJ} ${POWEROFFKILL_OBJ} ${REBOOTKILL_OBJ}

################################################################################
#
# End user target
#
#all: cinit cservice ccontrol sizecheck docs
all: ${ALLBIN}


################################################################################
#
# Generic
#
${OBJ}: ${CINIT_HEADERS}

%.o: %.c
	${CC} -c -o $@ $<

################################################################################
#
# First do configuration, so we include the right variables
#
Makefile: .configured

.configured: ../conf/*
	@../bin/cinit.configure.os
	@../bin/cinit.configure.tools
	@../bin/cinit.configure.ipc
	@../bin/cinit.configure.mark

${CINIT_OBJ}: ${CONFIG_H}

${CONFIG_H}: ../conf/*
	../scripts/cinit.mkheader > ${CONFIG_H}

################################################################################
#
# Install targets
#

#install: install-dir cinit cservice ccontrol
install: install-cinit install-utilities

install-sbin:
	install -d ${DESTDIR}/sbin

install-utilities: install-sbin ${BIN}
	@echo '*** Installing utilities ***'
	install ${BIN} ${DESTDIR}/sbin

install-cinit: install-sbin cinit
	@echo '*** Installing cinit ***'
	@echo "Need to delete cinit before reinstalling it {text file busy problem}"
	rm -f ${DESTDIR}/sbin/cinit
	install cinit ${DESTDIR}/sbin

# FIXME: target broken
install-miniconf:
	./bin/cinit.install.miniconf

# FIXME: target broken
install-dir:
	./bin/cinit.install.dir


################################################################################
#
# Build targets
#

cinit: ${CINIT_OBJ}
	${LD} $^ -o $@

cinit.halt: ${HALTKILL_OBJ}
	${LD} $^ -o $@

cinit.poweroff: ${POWEROFFKILL_OBJ}
	${LD} $^ -o $@

cinit.reboot: ${REBOOTKILL_OBJ}
	${LD} $^ -o $@

cmd: ${CMD_OBJ}
	${LD} $^ -o $@

################################################################################
#
# Internal test targets
#

uml: cinit cmd
	../../vm/uml/uml-mount.sh
	cp cinit cmd ../../vm/uml/root/sbin/
	../../vm/uml/uml-umount.sh

umlstart: uml
	../../vm/uml/uml-start.sh

################################################################################
#
# Clenaup targets
#

.PHONY: clean
.PHONY: dist
.PHONY: distclean

dist: distclean

distclean: clean
	rm -f os/current ipc/current .configured

clean:
	rm -f ../tmpbin/*.configured
	rm -f ${BIN} ${CINIT_OBJ} ${CINIT}
	rm -f client/*.o test/*.o
