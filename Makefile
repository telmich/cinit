# 
# 2005-2009 Nico Schottelius (nico-cinit at schottelius.org)
# 
# This file is part of cinit.
#
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
# along with cinit. If not, see <http://www.gnu.org/licenses/>.
#
#
# Don't edit Makefiles, use conf/* for configuration.
#

# Directories and files
CDIRS=src doc

#
# Targets
#

#
# Warn per default, make sure the user knows what she does
#
warn:
	@cat doc/.buildwarn

all: sources documentation
dev-all: all

install clean dist distclean:
	@for subdir in ${CDIRS}; do \
		echo "Making $@ in $$subdir"; \
		(cd $$subdir && ${MAKE} ${MAKEFLAGS} $@) || break; \
	 done;

.PHONY: sources
sources:
	${MAKE} -C src all

.PHONY: documentation
documentation:
	${MAKE} -C doc documentation

install-miniconf:
	./bin/cinit.install.miniconf

install-dir:
	./bin/cinit.install.dir

config:
	@./bin/cinit.configure.os
	@./bin/cinit.configure.tools
	@./bin/cinit.configure.ipc
	@touch src/.configured

################################################################################
# Tests
#
tests:
	# does not work, due getting killed, due to design :-)
	#./scripts/internal/compile_run_as_compiler.sh
	./scripts/internal/test_on_hosts.sh ./scripts/internal/compile_test.sh

### User Mode Linux / DIRECTORY
UML_DIR_OS_DEBIAN=lenny
UML_ROOT_DIR=~/cinit/vm/uml/$(UML_DIR_OS_DEBIAN)
UML_ROOT_DIR_ABS=$(shell cd $(UML_ROOT_DIR) && pwd -P)
CONFDIR=etc/cinit/

uml-install-debian:
	mkdir -p $(UML_ROOT_DIR)
	sudo /usr/sbin/debootstrap $(UML_DIR_OS_DEBIAN) $(UML_ROOT_DIR)
	me=$$(whoami); sudo chown -R $$me $(UML_ROOT_DIR)

# only install binaries, no need to test documentation
uml-install-config:
	rsync -av --delete ./$(CONFDIR) $(UML_ROOT_DIR)/$(CONFDIR)

uml-install-cinit:
	dir=$$(cd $(UML_ROOT_DIR); pwd -P); make -C src DESTDIR=$$dir install 

uml-dir-start-cinit: uml-install-config
	dir=$$(cd $(UML_ROOT_DIR); pwd -P); linux root=/dev/root rootflags=$$dir rootfstype=hostfs init=/sbin/cinit

uml-dir-start-plain:
	./scripts/vm/uml-dir-start-plain.sh $(UML_ROOT_DIR_ABS)

### User Mode Linux / IMAGE
UML_IMG_FILE=~/cinit/vm/uml/Debian-3.0r0.ext2
uml-img-start-cinit:
	./scripts/vm/uml-img-start-cinit.sh $(UML_IMG_FILE)

uml-img-start-plain:
	./scripts/vm/uml-img-start-plain.sh $(UML_IMG_FILE)

# debian-etch
de-install:
	rsync -av --delete ./ root@de:cinit
	rsync -av --delete ./etc/cinit/ root@de:/etc/cinit
	ssh root@de '(cd cinit; make clean install)'

de-run:
	ssh root@de reboot

UBUNTUHOST=cinit@192.168.122.107
UBUNTUCONF=./etc/cinit-ubuntu
UBUNTUINSTALL="cd cinit && make clean && sudo make install"
UBUNTUTEST="sudo reboot"
ubuntu-sync:
	rsync -av --delete ./ $(UBUNTUHOST):cinit
ubuntu-install: ubuntu-sync
	ssh "$(UBUNTUHOST)" $(UBUNTUINSTALL)

ubuntu-test: ubuntu-install
	ssh "$(UBUNTUHOST)" $(UBUNTUTEST)

################################################################################
# 
# Developer targets
#

release: ./scripts/internal/cinit.release
	./scripts/internal/cinit.release now

scripts/internal/cinit.release: ./scripts/internal/test-cmd.sh
	./scripts/internal/test-cmd.sh

WEBFILE=~/privat/computer/net/netzseiten/www.nico.schottelius.org/src/software/cinit.mdwn
.PHONY: web
web: README
	cp $< $(WEBFILE)

cinitconfconfdir=../cinit-conf/conf
sync-conf:
	 rsync --delete -av ./conf/ $(cinitconfconfdir)
	 cd $(cinitconfconfdir); git add .; git commit -m "sync with cinit/conf"
