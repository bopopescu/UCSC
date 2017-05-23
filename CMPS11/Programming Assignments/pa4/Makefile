# A simple Makefile for the Roots program
# Seongwoo choi
# Programming Assignment 4
# CMPS 11
#
#
Roots: Roots.class
echo Main-class: Roots > Manifest
	jar cvfm Roots Manifest Roots.class rm Manifest
	chmod u+x Roots
Roots.class: Roots.java
	javac -Xlint Roots.java
clean:
	rm -f Roots.class Roots
submit: Makefile Roots.java
	submit cmps011-pt.w15 pa4 Makefile Roots.java
Check:
	ls  /afs/cats.ucsc.edu/class/cmps011-pt.w15/pa4/scho29
