#-----------------------------------------------------------------------
#Seongwoo Choi
#scho29
#CMPS 12B/M
#Makefile for pa2
#-----------------------------------------------------------------------

JAVASRC = Search.java
SOURCES = README Makefile $(JAVASRC)
MAINCLASS = Search
CLASSES = Search.class
JARFILE = Search
SUBMIT = submit cmps012b-pt.s15 pa2

all: $(JARFILE)

$(JARFILE): $(CLASSES)
		echo Main-class: $(MAINCLASS) > Manifest
		jar cvfm $(JARFILE) Manifest $(CLASSES)
		rm Manifest
		chmod +x $(JARFILE)

$(CLASSES): $(JAVASRC)
		javac -Xlint $(JAVASRC)

clean:
		rm $(CLASSES) $(JARFILE)

submit: $(SOURCES)
		$(SUBMIT) $(SOURCES)
