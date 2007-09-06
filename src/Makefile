#
# cinit
#
# Nico Schottelius
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
BIN=halt.kill poweroff.kill reboot.kill cmd
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

halt.kill: ${HALTKILL_OBJ}
	${LD} $^ -o $@

poweroff.kill: ${POWEROFFKILL_OBJ}
	${LD} $^ -o $@

reboot.kill: ${REBOOTKILL_OBJ}
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

.PHONY: dist
dist: distclean

.PHONY: distclean
distclean: clean
	rm -f os/current ipc/current .configured

.PHONY: clean
clean:
	rm -f ../tmpbin/*.configured
	rm -f ${BIN} ${CINIT_OBJ} ${CINIT}
	rm -f client/*.o test/*.o
