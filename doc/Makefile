#
# Makefile stolen from ccollect
# Nico Schottelius, Fri Jan 13 12:13:08 CET 2006
#

ASCIIDOC=asciidoc
DOCBOOKTOTEXI=docbook2x-texi
DOCBOOKTOMAN=docbook2x-man
XSLTPROC=xsltproc
XSL=/usr/share/xml/docbook/stylesheet/nwalsh/html/docbook.xsl

#
# Asciidoc will be used to generate other formats later
#
MANDOCS  	= man/cinit.text
USERDOCS  	= user/compiles.on.text user/configuring.cinit.text 				\
				  user/conf-system.text                                        \
				  user/cross-compiling.text user/current-init-problems.text    \
				  user/daemons.backgrounding.text user/dependencies.text       \
				  user/example-directory-structure.text                        \
				  user/installing-cinit.text user/paths.text                   \
				  user/profiles.text user/README.text
DEVELDOCS 	= devel/codingguideline.text
DOCS     	= $(MANDOCS) $(USERDOCS) $(DEVELDOCS)

#
# Doku
#
HTMLDOCS = $(DOCS:.text=.html)
DBHTMLDOCS = $(DOCS:.text=.htm)

TEXIDOCS = $(DOCS:.text=.texi)

MANPDOCS = $(MANDOCS:.text=.man)

DOCBDOCS = $(DOCS:.text=.docbook)

DOC_ALL  = $(HTMLDOCS) $(DBHTMLDOCS) $(TEXIDOCS) $(MANPDOCS)

#
# End user targets
#
help:
	@echo "----------- documentation make targets --------------"
	@echo "documentation:    generate HTML, Texinfo and manpage"
	@echo "html:             only generate HTML (via asciidoc/docbook/xsltproc)"
	@echo "htm:              only generate HTML (via asciidoc)"
	@echo "info:             only generate Texinfo"
	@echo "man:              only generate manpage(s)"

install:

#
# Internal targets
#
html: 			$(HTMLDOCS)
htm:  			$(DBHTMLDOCS)
info: 			$(TEXIDOCS)
man:  			$(MANPDOCS) 
documentation: $(DOC_ALL)


#
# Generic targets
#

# docbook gets .htm, asciidoc directly .html (or the other way round)
%.html: %.docbook
	${XSLTPROC} -o $@ ${XSL} $<

%.htm: %.text
	${ASCIIDOC} -n -o $@ $<

%.docbook: %.text
	${ASCIIDOC} -n -b docbook -o $@ $<

%.texi: %.docbook
	${DOCBOOKTOTEXI} --to-stdout $< > $@

%.mandocbook: %.text
	${ASCIIDOC} -b docbook -d manpage -o $@ $<

%.man: %.mandocbook
	${DOCBOOKTOMAN} --to-stdout $< > $@

#
# Distribution
#
clean distclean:
	rm -f $(DOC_ALL)

#
# Be nice with the users and generate documentation for them
#
dist: distclean documentation

