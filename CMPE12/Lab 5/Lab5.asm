;Seongwoo Choi
;CMPE 12
;Lab 5
;T/Th 2:00PM - 4:00PM

	.ORIG   x3000		; this sets where the following
			; code will start in memory 
ONE	LEA	R0, HELLO	; R0 - HELLO
	ADD	R1, R1, R0	
	ADD	R1, R1, 5
Count	TRAP	x25	; displays HELLO.
	ADD	R1, R1, R0
	BRp	Count
	TRAP	x25	; this HALTS the program

; Here is some data declarations, we will learn more about these soon

HELLO:	.STRINGZ		"Hello, World, this is Seongwoo Choi!\n"

times	.FILL	x005	;prints 5 times
	.END		;ends the program.
