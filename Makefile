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
		(cd $$subdir && ${MAKE} ${MAKEFLAGS} $@); \
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

################################################################################
# old
#DDOC=ddoc
#SDIRS=bin client conf comm doc generic serv util
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
#clean:
#	$(MAKE) -C src clean
#	rm -f tmpbin/*
################################################################################
#cservice: $(SBIN)/cservice
#
#$(SBIN)/cservice util/cservice: $(SBIN) $(CSVC_OBJ)
#	$(LD) $(LDFLAGS) $(CSVC_OBJ) -o $@
#	$(STRIP) $@
#
#ccontrol: $(SBIN)/ccontrol
#
#$(SBIN)/ccontrol util/ccontrol: config.h $(SBIN) $(CCO_OBJ)
#	$(LD) $(LDFLAGS) $(CCO_OBJ) -o $@
#	$(STRIP) $@
#
#install:: install-dir cinit cservice ccontrol
#	@echo '*** Installing cinit ***'
#	./bin/cinit.install.binary
