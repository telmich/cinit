#
# cinit
# Nico Schottelius
#
# Don't edit Makefiles, use conf/* for configuration.
#

include Makefile.include

# directories and files
DDOC=ddoc
SDIRS=bin client conf comm doc generic serv util
CDIRS=contrib+tools
FILES=Changelog Makefile README TODO cinit.h

# objects
SERV=serv/sigio.o serv/cinit.o serv/list.o  \
     serv/run_init_svc.o serv/panic.o serv/sig_reboot.o \
     serv/sig_child.o

CLIENT=client/msg_svc_on_off.o client/msg_change_status.o client/run_svc.o \
       client/exec_svc.o client/respawn_svc.o client/run_run_svcs.o \
       client/connect_sock.o client/begin_msg.o client/sig_terminate.o

COMMUNICATION=comm/do_change_status.o comm/do_result.o comm/do_svc_name.o

BOTH=generic/set_signals.o generic/mini_printf.o generic/usage.o

OBJ=$(SERV) $(CLIENT) $(BOTH) $(COMMUNICATION)

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

all:: cinit cservice ccontrol sizecheck docs

cinit: $(CINIT_BIN)

docs: $(DDOC) bin/cdoc-man.sh
	./bin/cdoc-man.sh doc/cinit-doc     > $(DDOC)/cinit.8
	./bin/cdoc-man.sh doc/cservice-doc  > $(DDOC)/cservice.8

$(DDOC):
	mkdir $(DDOC)

$(CSVC_OBJ) $(OBJ): config.h

$(CINIT_BIN): $(SBIN) $(OBJ)
	$(LD) $(LDFLAGS) $(OBJ) -o $@
	$(STRIP) $@

$(SBIN):
	mkdir $(SBIN)

sizecheck: cinit cservice
	FILE="size/`date +%Y-%m-%d-%T`"; ls -l sbin/ > $$FILE; cat $$FILE
	@echo -n "Source size (in KiB): "
	@du -s $(SDIRS) | awk '{ sum+=$$1 } END { print sum }'
#	@du -s bin client comm conf doc generic serv | awk '{ sum+=$1 } END { print sum }'

clean::
	rm -f *.o */*.o sbin/* config.h ddoc/*

config.h: conf/*
	./bin/cinit.mkheader > config.h

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

all install clean::
	@for subdir in $(CDIRS); do \
	  echo "Making $@ in $$subdir"; \
	(cd $$subdir && $(MAKE) $(MAKEFLAGS) $@) \
	 || exit 1;\
	 done;
