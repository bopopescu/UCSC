#makefile------------------------------------------------------------------------------
# Seongwoo Choi
# Laboratory Assignment 6
# CS 12B/M 
# Makefile for CMPS 12B lab6
#------------------------------------------------------------------------------

JAVAC      = javac 
MAINCLASS  = ListClient
JAVASRC    = $(wildcard *.java)
SOURCES    = $(JAVASRC) makefile README List.java ListTest.java ListInterface.java ListIndexOutOfBoundsException.java ListClient.java
CLASSES    = $(patsubst %.java, %.class, $(JAVASRC))
JARCLASSES = $(patsubst %.class, %*.class, $(CLASSES))
JARFILE    = $(MAINCLASS) 
SUBMIT     = submit cmps012b-pt.u14 lab6


all: $(JARFILE)

$(JARFILE): $(CLASSES)
	echo Main-class: $(MAINCLASS) > Manifest
	jar cvfm $(JARFILE) Manifest $(JARCLASSES)
	chmod +x $(JARFILE)
	rm Manifest

%.class: %.java
	$(JAVAC) $<

clean:
	rm -f *.class $(JARFILE)

submit:
	${SUBMIT} ${SOURCES}