;Seongwoo Choi
;scho29@ucsc.edu
;CMPE 12
;Fall 2015
;Lab 6
;M/W 2:00PM - 4:00PM
;TA: Megan

	.ORIG	x3000
;clearing the registers
START:
	AND	R0, R0, 0
	AND	R1, R0, 0
	AND	R2, R0, 0
	AND	R3, R0, 0
	AND	R4, R0, 0
	AND	R5, R0, 0
	AND	R6, R0, 0
	AND	R7, R0, 0

; Getting the number 1
	LEA	R0, GREETING1
	PUTS


GETCHAR	GETC
	PUTC
	;did the user press X?
	LD	R6, X
	ADD	R6, R6, R0
	BRz	END

	; check if LF
	ADD	R3, R0, #-10
	BRz	NEWLINE

	; check if '-'
	LD	R4, DASH
	ADD	R3, R0, R4
	BRz	SetF

	; subtract 48 to convert ASCII to decimal
	LD	R4, ASCII0
	ADD	R3, R0, R4
	
	;Setting up registers for multiplication
	AND	R4, R4, 0
	ADD	R4, R4, #10	;using R4 as a counter
	AND	R5, R5, 0

; loop for multiplying by 10
MULT	ADD	R5, R5, R1 
	ADD	R4, R4, #-1	 	
	BRp	MULT
	ADD	R1, R5, R3	;INT == Int X 10+digit
	BR	GETCHAR

	;CF = checkflag
SetF	ADD	R2, R2, 1	;Updating flag into R2
	BR	GETCHAR

NEWLINE	
	;is flag == 1
	AND	R2, R2, 1
	BRnz	MASKER
	
; convert to 2s complement if flag == 1
TWOSC	NOT	R1, R1
	ADD	R1, R1, #1
	
MASKER	LEA	R0, GREETING2
	PUTS
	LEA	R3, MASK
	AND	R4, R4, #0
	ADD	R4, R4, #15
LOOP	LDR	R2, R3, 0	;R2 is grabbing the data R3's location
	LD	R0, ASCIIzero	;load ascci '0'
	ADD	R3, R3, #1	
	AND	R5, R1, R2	;R2 contains MASK, R1 contains integer that needs to be converted into binary
	BRz	ZERO		;move to print zero
	
	ADD 	R0, R0, #1
ZERO	PUTC
	ADD	R4, R4, #-1
	BRzp	LOOP		;if the counter is greater than or equal to zero, then go back to the loop.
	BR	START
	
		
END	LEA	R0, GREETING3
	PUTS
HALT				;Halting the program

DASH		.FILL		#-45
ASCII0		.FILL		#-48
ASCIIzero	.FILL		#48
INT		.FILL		x0
COUNTER		.FILL		#10

X		.FILL		#-88
MASKptr		.FILL		x0

MASK		.FILL		x8000
		.FILL		x4000
		.FILL		x2000
		.FILL		x1000
		.FILL		x0800
		.FILL		x0400
		.FILL		x0200
		.FILL		x0100
		.FILL		x0080
		.FILL		x0040
		.FILL		x0020
		.FILL		x0010
		.FILL		x0008
		.FILL		x0004
		.FILL		x0002
		.FILL		x0001


GREETING1	.STRINGZ	"\nWelcome to the conversion program\nEnter a decimal number or X to quit:\n"
GREETING2	.STRINGZ	"Thanks, here it is in binary\n"
GREETING3	.STRINGZ	"\nBye. Have a great day.\n"
		
		.END