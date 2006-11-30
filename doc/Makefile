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
MANDOCS  = man/cinit.text
DOCS     = $(MANDOCS)

#
# Doku
#
HTMLDOCS = $(DOCS:.text=.html)
DBHTMLDOCS = $(DOCS:.text=.htm)

TEXIDOCS = $(DOCS:.text=.texi)

MANPDOCS = $(MANDOCS:.text=.man)

DOCBDOCS = $(DOCS:.text=.docbook)

DOC_ALL  = $(HTMLDOCS) $(DBHTMLDOCS) $(TEXIDOCS) $(MANPDOCS)

html: $(HTMLDOCS)
htm: $(DBHTMLDOCS)
info: $(TEXIDOCS)
man: $(MANPDOCS) 
documentation: $(DOC_ALL)

#
# End user targets
#
all:
	@echo "----------- documentation make targets --------------"
	@echo "documentation:    generate HTMl, Texinfo and manpage"
	@echo "html:             only generate HTML"
	@echo "info:             only generate Texinfo"
	@echo "man:              only generate manpage(s)"

install:

# docbook gets .htm, asciidoc directly .html
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
allclean:
	rm -f $(DOC_ALL)

distclean:
	rm -f $(DOCBDOCS)

#
# Be nice with the users and generate documentation for them
#
dist: distclean documentation
