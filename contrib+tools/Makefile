#
# (c) 2005 Peter Portmann (pp at bluewin.ch)
# cinit/contrib+tools
#     
# This script is written for the clinux-System and published
# under the terms of GPL 2.0
#
# Version: 0.1
#
# ChangeLog:
#
# Todo:
#
# Features:

#
# compile/link options
#
# do not use DEBUG and OPTIMIZE at the same time!
#DEBUG=-DDEBUG
#OPTIMIZE=-Werror 
#DEBUG=-g -DDEBUG
OPTIMIZE=-pipe -Os -Werror 

# init should be static per default!
LDFLAGS=     

# programs
CC=gcc $(DEBUG) $(OPTIMIZE) $(TIMEME)
CFLAGS=-Wall -I. -I../
LD=gcc
STRIP=strip -R .comment -R .note

INSTALL = install

prefix = $(HOME)
bindir = $(prefix)/bin

# objects

CLIENT=cinit.graph.text.o 

COMMUNICATION=error.o ../generic/usage.o ../generic/mini_printf.o

OBJ=$(CLIENT) $(COMMUNICATION)

#
PROGRAMS=cinit.graph.text
SCRIPTS=cconfig.graph.xml.rb \
	make.cconfig.from.xml.rb \
	cinit-vis.pl \
	cinit-vis-killerfox.pl

# targets
all: $(PROGRAMS)

cinit.graph.text: $(OBJ)
	$(LD) $(LDFLAGS) $(OBJ) -o $@
	$(STRIP) $@

clean:
	rm -f *.o
	rm -f $(PROGRAMS)

install: all
	@echo '*** Installing contrib+tools ***'
	$(INSTALL) -d -m755 $(DESTDIR)$(bindir)
	$(INSTALL) $(PROGRAMS) $(SCRIPTS) $(DESTDIR)$(bindir)
