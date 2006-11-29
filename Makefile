#
# cinit
# Nico Schottelius
#
# Don't edit Makefiles, use conf/* for configuration.
#

# directories and files
DDOC=ddoc
SDIRS=bin client conf comm doc generic serv util
CDIRS=contrib+tools

# DO NOT CHANGE THIS.
SBIN=sbin
CINIT_BIN=$(SBIN)/cinit

# targets
warn:
	@cat doc/.buildwarn

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

all: sources sizecheck

sources:
	$(MAKE) -C src all

docs: $(DDOC) bin/cdoc-man.sh
	./bin/cdoc-man.sh doc/cinit-doc     > $(DDOC)/cinit.8
	./bin/cdoc-man.sh doc/cservice-doc  > $(DDOC)/cservice.8

$(DDOC):
	mkdir $(DDOC)

$(CSVC_OBJ) $(OBJ): $(CONFIG_H)

$(SBIN):
	mkdir $(SBIN)

sizecheck: sources
	FILE="size/`date +%Y-%m-%d-%H%M%S`"; ls -l src/cinit > $$FILE; cat $$FILE
	@echo -n "Source size (in KiB): "
	@du -s src/ | awk '{ sum+=$$1 } END { print sum }'

clean:
	$(MAKE) -C src clean
	rm -f tmpbin/*

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

#all install clean::
#	@for subdir in $(CDIRS); do \
#	  echo "Making $@ in $$subdir"; \
#	(cd $$subdir && $(MAKE) $(MAKEFLAGS) $@) \
#	 || exit 1;\
#	 done;

config:
	@./bin/cinit.configure.os
	@./bin/cinit.configure.tools
	@./bin/cinit.configure.ipc
	@touch src/.configured
