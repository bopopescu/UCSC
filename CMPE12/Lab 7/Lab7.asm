;Seongwoo Choi
;CMPE 12
;scho29@ucsc.edu
;Lab 7
;M/W: 2:00PM-4:00PM
;TA: Meagan


		.ORIG	x3000




GREETING	.STRINGZ		"\n\n\nHello,welcome to my Caesar Cipher program\n\n"
PROBLEM1	.STRINGZ		"Do you want to (E)ncrypt or(D)ecrypt or e(X)it?\r>"
CIPHER		.STRINGZ		"\n\nWhat is the cipher(1-25)?\r>"
STRING		.STRINGZ		"\n\nWhat is the string(up to 200 characters)?\r>"

START		AND 	R0, R0, 0	;clearing the registers
		AND	R1, R1, 0
		AND	R2, R2, 0
		AND	R3, R3, 0	
		AND	R4, R4, 0
		AND	R5, R5, 0
		AND	R6, R6, 0
		AND	R7, R7, 0

		LEA	R0, GREETING
		PUTS
		LEA	R0, PROBLEM1
		PUTS
		GETC
		PUTC
					;checking if the user pressed X
		LD	R1, X
		ADD	R2, R0, R1
		BRz	FINAL
;D/E-CHECK;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
		LD	R1, D
		ADD	R2, R0, R1
		ST	R2, OR		;E:69->R2=1;  D:68->R2=0

		LEA	R0, INVALID	;if the user pressed an alphabet letter other than D,E, X, then prints invalid
		PUTS
		BR	START

INVALID	 	.STRINGZ 	"\nInvalid Input\n"
;CIPHER;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
		LEA	R0, CIPHER
		PUTS
CIPH		GETC
		PUTC
		ADD	R1, R0, -10	;LF
		BRz	STRI1
		LD	R2, ASCII0
		ADD	R3, R0, R2	;
		ADD	R6, R6, 10
LOOP1		ADD	R5, R5, R4
		ADD	R6, R6, -1
		BRp	LOOP1
		ADD	R4, R5, R3	
		ST	R4, CA
		BR	CIPH		
;string input 
STRI1		LEA	R0, STRING
		PUTS
		LEA	R2, STACKPAC	;get the address of the array
		LD	R3, ZERO	;index (pointer)
		
INPUT		GETC
		PUTC

		ADD	R5, R2, R3	;get the corresponding location
		STR	R0, R5, 0	;store the value into the array
		ADD	R3, R3, 1	;move to the next index
;LF check 
		ADD	R1, R0, -10
		BRnp	INPUT
		
		AND	R0, R0, 0
		AND	R1, R1, 0
		AND	R2, R2, 0
		AND	R3, R3, 0	
		AND	R4, R4, 0
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;checks if the user pressed D/E. 

		LD	R1, OR
		BRz	YES

NO		LEA	R0, DECRYPTED
		PUTS
		BR	POINTER

YES		LEA	R0, ENCRYPTED
		PUTS
		BR	POINTER
		
POINTER		LEA	R2, STACKPAC
		LD	R3, ZERO	;pointer
NEXT		ADD	R4, R2,R3	;address 
		LDR	R0, R4, 0	;read
		ADD	R1, R0, -10
		BRz	CHECK
		ADD	R0, R0, 0
		OUT
		ADD	R3, R3, 1
		BR	NEXT	

CHECK		AND 	R0, R0, 0	;print row1
		AND	R1, R1, 0
		AND	R2, R2, 0
		AND	R3, R3, 0	
		
		LD	R1, OR
		BRz	DECRYPTION
		LEA	R0, NL
		PUTS
		LEA	R0, ENCRYPTED
		PUTS
		JSR	CODE
		AND 	R0, R0, 0
		AND	R1, R1, 0
		AND	R2, R2, 0
		AND	R3, R3, 0	
		AND	R4, R4, 0
		AND	R5, R5, 0
		AND	R6, R6, 0
		BR	POINTER1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;		
ENCRYPTION	LEA	R0, ENCRYPTED 	;algorithm for encryption
		PUTS		
		JSR	CODE
		AND 	R0, R0, 0
		AND	R1, R1, 0
		AND	R2, R2, 0
		AND	R3, R3, 0	
		AND	R4, R4, 0
		AND	R5, R5, 0
		AND	R6, R6, 0
		BR	POINTER1

DECRYPTION	LEA	R0, NL		;algorithm for decryption
		PUTS
		LEA	R0, DECRYPTED
		PUTS		
		JSR	CODE
		AND 	R0, R0, 0
		AND	R1, R1, 0
		AND	R2, R2, 0
		AND	R3, R3, 0	
		AND	R4, R4, 0
		AND	R5, R5, 0
		AND	R6, R6, 0
		BR	POINTER1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;these lines of code show if the pointer is at the back of the array. 
POINTER1	LEA	R2, STACKPAC
		LD	R3, R_O
LOOP2		ADD	R4, R2, R3	
		LDR	R0, R4, 0	
		ADD	R1, R0, -10	;LF?
		BRz	START		;if end of array, back to begin
		ADD	R0, R0, 0	;if the user pressed char bigger, then this loop works
		OUT
		ADD	R3, R3, 1
		BR	LOOP2

;END the program
FINAL		LEA	R5, MSG2
		ADD	R5, R5, R0
		HALT	

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;an algorithm that checks the uppercase and the lowercase value of the alphabet from the user input.
CODE		ST	R7, ADDRE
		LEA	R2, STACKPAC
		LD	R3, ZERO	;pointer at R3 
LOOP		ADD	R5, R2, R3	;R2=address in array
		LDR	R0, R5, 0	;load the value from row0 to R0
			
		LD	R1, A		;A=-65
		ADD	R1, R0, R1	
		BRn	STORE		;If<0, this indicates that char is special char, so store it
		LD	R1, Z		;Z=-90
		ADD	R1, R0, R1	;65=<char=<90
		BRnz 	UPPERCASE	;if negative/Zero, means char is uppercase, store it to the location that is indicated. 
		LD	R1, a		;R1 now stores -97, remaining should be char>90
		ADD	R1, R0, R1	;if <0, means it's special char (91-96)	
		BRn	STORE		;remaining should be >=97
		LD	R1, z		;R1=-122
		ADD	R1, R0, R1	;check 97=<char<=122
		BRnz	LOWERCASE	;if n/z, means lowercase
		BRp	STORE		;if p, means char>122->special char

STORE		LD	R4, R_O		;row_1=200, store special char to row 1
		ADD	R6, R5, R4	
		STR	R0, R6, 0	;store R0 to row1

		ADD	R1, R0, -10	;LF
		BRz	RETURN		;if LF which means end of input, halt subroutine

		ADD	R3, R3, 1	;move to the next index in row0
		BR	LOOP


UPPERCASE	LD	R6, CA		;R6=CA
		LD	R1, Q		;R1 now replaced with -77 (Q)
		ADD	R1, R0, R1	;R1=R0-77
		BRnz	LAST		;if n/z, means 65<=char=<77 (A-Q)
		NOT	R6, R6		;if p, means 78-90
		ADD	R6, R6, 1
		ADD	R0, R0, R6	;if N-Z, R0=R0-CA
		LD	R1, A
		ADD	R1, R1, R0
		BRzp	CIA
		LD	R1, TS
		ADD	R0, R0, R1	;<65,+26
CIA		BR	STORE		;store it to row1
LAST		ADD	R0, R0, R6	;if A-M, R0=R0+CI
		LD	R1, Z
		ADD	R1, R1, R0
		BRnz	WO
		LD	R1, TS
		NOT	R1, R1
		ADD	R1, R1, 1	;-26
		ADD	R0, R0, R1	;>90,-26	
WO		BR	STORE		;store it to row1

LOWERCASE	LD	R6, CA
		LD	R1, W		;R1=-109(W)
		ADD	R1, R0, R1	
		BRnz	FIRST		;if n/z, which means 97<=char=<109
		NOT	R6, R6		;-CA
		ADD	R6, R6, 1		
		ADD	R0, R0, R6	;R0=R0-CA
		LD	R1, a
		ADD	R1, R1, R0
		BRzp	AI
		LD	R1, TS
		ADD	R0, R0, R1	;<97, +26
AI		BR	STORE
FIRST		ADD	R0, R0, R6	;R0 = R0+CA
		LD	R1, z
		ADD	R1, R1, R0
		BRnz	FOO
		LD	R1, STACKPAC
		NOT	R1, R1
		ADD	R1, R1, 1 	;>90, -26
		ADD	R0, R0, R1						
FOO		BR	STORE

RETURN		LD	R7, ADDRE
		RET

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;	

ENCRYPTED	.STRINGZ		"<Encrypted>"
DECRYPTED	.STRINGZ		"<Decrypted>"		
X		.FILL			-88
D		.FILL			-68
A		.FILL			-65
Z		.FILL			-90
a		.FILL			-97
z		.FILL			-122
Q		.FILL			-77
W		.FILL			-109
ADDRE		.FILL			0
OR		.FILL			0
ZERO		.FILL			0
CA		.FILL			0
ASCII0		.FILL			-48
PROBLEM3	.STRINGZ		"Here is your string and the decrypted result\r"
MSG2		.STRINGZ		"Goodbye!"
R_O		.FILL			200
NL		.STRINGZ		"\n"
TS		.FILL			26
STACKPAC	.BLKW			400

		.END