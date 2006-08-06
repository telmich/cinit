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
CINIT_IPC_OBJ=$(shell cat ipc/current/objects)
CINIT_OS_OBJ=$(shell cat os/current/objects)
CINIT_OBJ=$(CINIT_CORE_OBJ) $(CINIT_IPC_OBJ) $(CINIT_OS_OBJ)
CINIT_HEADERS=$(shell cat headers/listing)

#
# Dependencies
#
$(CINIT_OBJ): $(CINIT_HEADERS)

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

%.o: %.c
	$(CC) -c -o $@ $<

#
# End user targets
#
#all:: config cinit cservice ccontrol sizecheck docs
#all: testconfig cinit cservice ccontrol sizecheck docs
all:: .configured cinit cservice ccontrol sizecheck docs

.configured: ../conf/*
	@if [ ! -e .configured ]; then \
	   echo -n "Please run \"make config\" in parent directory: " ; \
	   echo "\"(cd ..; make config)\""; \
	fi; \
	exit 1

$(CINIT_OBJ): $(CONFIG_H)

cinit: $(CINIT_OBJ)
	$(LD) $^ -o $@


#$(CINIT_BIN): $(SBIN) $(OBJ)
#	$(LD) $(LDFLAGS) $(OBJ) -o $@
#	$(STRIP) $@

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
