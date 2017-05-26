//Seongwoo Choi
//scho29
//CMPS12B
//Makefile
//Creates an executable jar file Extrema 

Extrema: Extrema.class
	echo Main-class: Extrema > Manifest
	jar cvfm ComplexTest Manifest Extrema.class
	rm Manifest
	chmod u+x Extrema

Extrema.class: Extrema.java 
	javac -Xlint Extrema.java

Extrema.class: Extrema.java
	javac -Xlint Extrema.java

clean:
	rm -f Extrema.class

spotless: clean
	rm -f Extrema

submit:
	submit cmps012B-pt.s15 pa1 Extrema.java README Makefile