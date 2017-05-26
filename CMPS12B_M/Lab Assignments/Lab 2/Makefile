#-----------------------------------------------------------------------
#Seongwoo Choi
#scho29
#CMPS 12B/M
#Makefile for lab2
#-----------------------------------------------------------------------


JAVASRC = FileReverse.java
SOURCES = README Makefile $(JAVASRC)
MAINCLASS = FileReverse
CLASSES = FileReverse.class
JARFILE = FileReverse
SUBMIT = submit cmps012b-pt.s15 lab2

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
