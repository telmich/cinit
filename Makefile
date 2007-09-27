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

################################################################################
# 
# Developer targets
#

release: ./scripts/internal/cinit.release
	./scripts/internal/cinit.release now

scripts/internal/cinit.release: ./scripts/internal/test-cmd.sh
	./scripts/internal/test-cmd.sh

