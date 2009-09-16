#
# cinit
# Nico Schottelius
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
dev-all: all sizecheck

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

sizecheck: sources
	FILE="size/`date +%Y-%m-%d-%H%M%S`"; ls -l src/cinit > $$FILE; cat $$FILE; \
	cg-add $$FILE
	cg-commit $$FILE -m "Size added"
	#cg-commit $$FILE -m "Size: $$(awk '{ print $5 }' $$FILE)"

source-size: clean
	@echo -n "Source size (in KiB): "
	@du -s src/ | awk '{ sum+=$$1 } END { print sum }'


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

DEBIAN=lenny
UMLDIR=test/uml
CONFDIR=etc/cinit/

uml-install-debian:
	mkdir -p $(UMLDIR)
	sudo /usr/sbin/debootstrap $(DEBIAN) $(UMLDIR)
	me=$$(whoami); sudo chown -R $$me $(UMLDIR)

# only install binaries, no need to test documentation
uml-install-config:
	rsync -av --delete ./$(CONFDIR) $(UMLDIR)/$(CONFDIR)

uml-install-cinit:
	dir=$$(cd $(UMLDIR); pwd -P); make -C src DESTDIR=$$dir install 

uml-run: uml-install-config
	dir=$$(cd $(UMLDIR); pwd -P); linux root=/dev/root rootflags=$$dir rootfstype=hostfs init=/sbin/cinit

uml-run-sysv:
	dir=$$(cd $(UMLDIR); pwd -P); linux root=/dev/root rootflags=$$dir rootfstype=hostfs

# debian-etch
de-install:
	rsync -av --delete ./ root@de:cinit
	rsync -av --delete ./etc/cinit/ root@de:/etc/cinit
	ssh root@de '(cd cinit; make clean install)'

de-run:
	ssh root@de reboot

UBUNTUHOST=cinit@192.168.122.2
UBUNTUCONF=./etc/cinit-ubuntu
UBUNTUINSTALL="cd cinit && make clean && sudo make install"
UBUNTUTEST="sudo reboot"
ubuntu-install:
	rsync -av --delete ./ $(UBUNTUHOST):cinit
#	rsync -av --delete ./$(UBUNTUCONF) $(UBUNTUHOST):/etc/cinit
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

cinitconfconfdir=../cinit-conf/conf
sync-conf:
	 rsync --delete -av ./conf/ $(cinitconfconfdir)
	 cd $(cinitconfconfdir); git add .; git commit -m "sync with cinit/conf"

