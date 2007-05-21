#
# cinit
#
# Nico Schottelius
#
# Don't edit Makefiles, use conf/* for configuration.
#

#include Makefile.tests

# Build tools / locations
CC=../tmpbin/cc
CFLAGS=
LD=../tmpbin/ld
LDFLAGS=
STRIP=../tmpbin/strip
SBIN=../sbin

# directories and files
CONFIG_H=include/config.h

BIN=cinit halt.kill poweroff.kill reboot.kill cmd

#
# All objects depend on headers. More or less. FIXME: use gcc -M
#
CINIT_HEADERS=$(shell cat include/listing)

CINIT_OBJ=$(shell cat object_lists/cinit)
HALTKILL_OBJ=$(shell cat object_lists/halt.kill)
POWEROFFKILL_OBJ=$(shell cat object_lists/poweroff.kill)
REBOOTKILL_OBJ=$(shell cat object_lists/reboot.kill)
CMD_OBJ=$(shell cat object_lists/cmd)

#
# Client modules
#
OBJ=$(CINIT_OBJ) $(HALTKILL_OBJ) $(POWEROFFKILL_OBJ) $(REBOOTKILL_OBJ)

#
# End user target
#
#all: cinit cservice ccontrol sizecheck docs
all: $(BIN)


#
# Generic
#
$(OBJ): $(CINIT_HEADERS)

%.o: %.c
	$(CC) -c -o $@ $<



#
# First do configuration, so we include the right variables
#
Makefile: .configured

.configured: ../conf/*
	@../bin/cinit.configure.os
	@../bin/cinit.configure.tools
	@../bin/cinit.configure.ipc
	@../bin/cinit.configure.mark

$(CINIT_OBJ): $(CONFIG_H)


$(CONFIG_H): ../conf/*
	../scripts/cinit.mkheader > $(CONFIG_H)

cservice: $(SBIN)/cservice

$(SBIN)/cservice util/cservice: $(SBIN) $(CSVC_OBJ)
	$(LD) $(LDFLAGS) $(CSVC_OBJ) -o $@
	$(STRIP) $@

ccontrol: $(SBIN)/ccontrol

$(SBIN)/ccontrol util/ccontrol: config.h $(SBIN) $(CCO_OBJ)
	$(LD) $(LDFLAGS) $(CCO_OBJ) -o $@
	$(STRIP) $@

#install: install-dir cinit cservice ccontrol
install: $(BIN)
	@echo '*** Installing cinit ***'
	cp $^ /sbin
#	./bin/cinit.install.binary

install-miniconf:
	./bin/cinit.install.miniconf

install-dir:
	./bin/cinit.install.dir


################################################################################
#
# Build targets
#
cinit: $(CINIT_OBJ)
	$(LD) $^ -o $@

halt.kill: $(HALTKILL_OBJ)
	$(LD) $^ -o $@

poweroff.kill: $(POWEROFFKILL_OBJ)
	$(LD) $^ -o $@

reboot.kill: $(REBOOTKILL_OBJ)
	$(LD) $^ -o $@

cmd: $(CMD_OBJ)
	$(LD) $^ -o $@

uml: cinit
	../../vm/uml/uml-mount.sh
	cp cinit ../../vm/uml/root/sbin/cinit
	../../vm/uml/uml-umount.sh

umlstart: uml
	../../vm/uml/uml-start.sh

################################################################################
#
# Generic targets
#

.PHONY: dist
dist: distclean

.PHONY: distclean
distclean: clean
	rm -f os/current ipc/current .configured

.PHONY: clean
clean:
	rm -f ../tmpbin/*.configured
	rm -f $(BIN) $(CINIT_OBJ)
	rm -f client/*.o test/*.o
