#
# cinit
# Nico Schottelius
#
# Don't edit Makefiles, use conf/* for configuration.
#

# directories and files
CDIRS=contrib+tools

# targets
warn:
	@cat doc/.buildwarn

all: sources sizecheck

.PHONY: sources
sources:
	$(MAKE) -C src all

.PHONY: docs
docs:
	$(MAKE) -C doc all

sizecheck: sources
	FILE="size/`date +%Y-%m-%d-%H%M%S`"; ls -l src/cinit > $$FILE; cat $$FILE; \
	cg-add $$FILE

clean:
	$(MAKE) -C src clean
	rm -f tmpbin/*

source-size: clean
	@echo -n "Source size (in KiB): "
	@du -s src/ | awk '{ sum+=$$1 } END { print sum }'

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

config:
	@./bin/cinit.configure.os
	@./bin/cinit.configure.tools
	@./bin/cinit.configure.ipc
	@touch src/.configured

################################################################################
# old
#DDOC=ddoc
#SDIRS=bin client conf comm doc generic serv util
#all install clean::
#	@for subdir in $(CDIRS); do \
#	  echo "Making $@ in $$subdir"; \
#	(cd $$subdir && $(MAKE) $(MAKEFLAGS) $@) \
#	 || exit 1;\
#	 done;
# DO NOT CHANGE THIS.
#SBIN=sbin
#CINIT_BIN=$(SBIN)/cinit
#
#%.o: %.c
#	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<
#$(DDOC):
#	mkdir $(DDOC)
#
#$(SBIN):
#	mkdir $(SBIN)
#
#docs: $(DDOC) bin/cdoc-man.sh
#	./bin/cdoc-man.sh doc/cinit-doc     > $(DDOC)/cinit.8
#	./bin/cdoc-man.sh doc/cservice-doc  > $(DDOC)/cservice.8
#$(CSVC_OBJ) $(OBJ): $(CONFIG_H)

