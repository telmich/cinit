#
# cinit
#
# Nico Schottelius
#
# Don't edit Makefiles, use conf/* for configuration.
#

# Build tools
CC=../tmpbin/cc
CFLAGS=
LD=../tmpbin/ld
LDFLAGS=
STRIP=../tmpbin/strip

# directories and files
CONFIG_H=headers/config.h

# objects for the cinit part
CINIT_CORE_OBJ=$(shell cat core/objects)
CINIT_IPC_OBJ=$(shell cat ipc/current/objects 2>/dev/null)
CINIT_OS_OBJ=$(shell cat os/current/objects 2>/dev/null)
CINIT_OBJ=$(CINIT_CORE_OBJ) $(CINIT_IPC_OBJ) $(CINIT_OS_OBJ)

#
# Client modules
#
CLIENT=client/msg_svc_on_off.o client/msg_change_status.o client/run_svc.o \
       client/exec_svc.o client/respawn_svc.o client/run_run_svcs.o \
       client/connect_sock.o client/begin_msg.o client/sig_terminate.o

COMMUNICATION=comm/do_change_status.o comm/do_result.o comm/do_svc_name.o

BOTH=generic/set_signals.o generic/mini_printf.o generic/usage.o

OBJ=$(SERV) $(SERV_OS) $(CLIENT) $(BOTH) $(COMMUNICATION)

CSVC_OBJ=util/cservice.o generic/mini_printf.o util/msg_reboot.o \
         generic/usage.o \
         $(CLIENT) $(COMMUNICATION)

CCO_OBJ=util/ccontrol.o generic/mini_printf.o util/msg_reboot.o \
         generic/usage.o \
         $(CLIENT) $(COMMUNICATION)

# DO NOT CHANGE THIS.
SBIN=sbin
CINIT_BIN=$(SBIN)/cinit

# targets
warn:
	@cat doc/.buildwarn

%.o: %.c
	$(CC) -c -o $@ $<

all:: config cinit cservice ccontrol sizecheck docs

cinit: $(CINIT_OBJ)
	echo $(LD) $(CFLAGS) -c -o $@ $<

docs: $(DDOC) bin/cdoc-man.sh
	./bin/cdoc-man.sh doc/cinit-doc     > $(DDOC)/cinit.8
	./bin/cdoc-man.sh doc/cservice-doc  > $(DDOC)/cservice.8

$(DDOC):
	mkdir $(DDOC)

$(CINIT_OBJ): $(CONFIG_H)

$(CINIT_BIN): $(SBIN) $(OBJ)
	$(LD) $(LDFLAGS) $(OBJ) -o $@
	$(STRIP) $@

$(SBIN):
	mkdir $(SBIN)

sizecheck: cinit cservice
	FILE="size/`date +%Y-%m-%d-%H%M%S`"; ls -l sbin/ > $$FILE; cat $$FILE
	@echo -n "Source size (in KiB): "
	@du -s $(SDIRS) | awk '{ sum+=$$1 } END { print sum }'
#	@du -s bin client comm conf doc generic serv | awk '{ sum+=$1 } END { print sum }'

#clean::
clean:
	echo rm  $(shell find -name \*.o)
	#rm -f sbin/* $(CONFIG_H) ddoc/*
	#rm -f tmpbin/*

distclean:
	rm -f os/current ipc/current

$(CONFIG_H): ../conf/*
	../bin/cinit.mkheader > $(CONFIG_H)

cservice: $(SBIN)/cservice

$(SBIN)/cservice util/cservice: $(SBIN) $(CSVC_OBJ)
	$(LD) $(LDFLAGS) $(CSVC_OBJ) -o $@
	$(STRIP) $@

ccontrol: $(SBIN)/ccontrol

$(SBIN)/ccontrol util/ccontrol: config.h $(SBIN) $(CCO_OBJ)
	$(LD) $(LDFLAGS) $(CCO_OBJ) -o $@
	$(STRIP) $@

install:: install-dir cinit cservice ccontrol
	@echo '*** Installing cinit ***'
	./bin/cinit.install.binary

install-miniconf:
	./bin/cinit.install.miniconf

install-dir:
	./bin/cinit.install.dir

all install::
	@for subdir in $(CDIRS); do \
	  echo "Making $@ in $$subdir"; \
	(cd $$subdir && $(MAKE) $(MAKEFLAGS) $@) \
	 || exit 1;\
	 done;

config:
	@../bin/cinit.configure.os
	@../bin/cinit.configure.tools
	@../bin/cinit.configure.ipc
