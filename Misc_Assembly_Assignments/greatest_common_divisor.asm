; Program: greatest_common_divisor
; Description: This program gets two signed integer values from the user.  It then tests the values
;				for validity, and then calculates their GCD and outputs it to STDOUT.

INCLUDE Irvine32.inc

;-----------------------
; Function Prototypes
;-----------------------
; GetUserValues	PROC
; TestValues	PROC
; GetAbsoluteValue	PROC
; DivideByZero		PROC
; CalcGcd	PROC
; DisplayGcd		PROC

.data
getXPrompt		BYTE	"Enter a 32 bit number: ", 0
getYPrompt		BYTE	0Dh, "Enter a 32 bit number: ", 0
resultPrompt	BYTE	0Ah, 0Dh, "Greatest common divisor is: ", 0
zeroPrompt		BYTE	0Ah, 0Dh, "Error: A value cannot be zero! Exiting...", 0Ah, 0

.code
main PROC
	; clear registers
	mov		eax, 0
	mov		ebx, 0
	mov		ecx, 0
	mov		edx, 0

	; get values from user
	call	GetUserValues

	; check values to be greater than zero
	call	TestValues

	; find greatest common divisor
	call CalcGcd
	
	; output result
	call DisplayGcd

	exit
main ENDP



; ---------------------------------------------------------
GetUserValues PROC
; Description: Prompts the user for two signed integer values and stores them in registers
; Receives: EBX = 0, EAX = 0
; Returns: EBX = First Value, EAX = Second Value
; ---------------------------------------------------------
	; prompt user for a first value
	mov		edx, OFFSET getXPrompt
	call	WriteString

	; get user first value
	call	ReadInt
	mov		ebx, eax

	; prompt user for a second value
	mov		edx, OFFSET getYPrompt
	call	WriteString
	
	; get user second value
	call	ReadInt

	ret
GetUserValues ENDP



; ---------------------------------------------------------
TestValues PROC
; Description: Checks to make sure the values are not zero, then checks checks for any negative
;				values.  If any values are negative, the GetAbsoluteValue function is called
;				and finds their twos complement.
; Receives: EBX = user value 1, EAX = user value 2
; Returns: EBX = positive user value 1, EAX = positive user value 2
;			carry flag set returns an zero error, else success
; ---------------------------------------------------------
	; check if either value is zero
	cmp eax, 0
	je ERROR_ZERO
	cmp ebx, 0
	jne testEAX

ERROR_ZERO:
	call DivideByZero

	; check if eax > 0, if less than zero, get twos complement
testEAX:
	cmp		eax, 0
	jg		testEBX
	mov		edx, eax
	call	GetAbsoluteValue
	mov		eax, edx

	; check if ebx > 0, if less than zero, get twos complement
testEBX:
	cmp		ebx, 0
	jg		next
	mov		edx, ebx
	call	GetAbsoluteValue
	mov		ebx, edx

next:
	ret
TestValues ENDP



; ---------------------------------------------------------
GetAbsoluteValue PROC USES eax
; Description: converts the incoming negative value to its twos complement,
;			   effectively getting its absolute value
; Receives: EDX = Negative value
; Returns: EDX = Positive value
; ---------------------------------------------------------
	mov		eax, edx

	; twos complement the negative value
	neg		eax

	mov		edx, eax
	ret
GetAbsoluteValue ENDP



; ---------------------------------------------------------
DivideByZero PROC
; Description: Prompts the user they cannot use zero as a value and exits
; Receives: Nothing
; Returns: Nothing
; ---------------------------------------------------------
	mov		edx, OFFSET zeroPrompt
	call	WriteString
	call	Crlf
	call	WaitMsg

	exit
DivideByZero ENDP



; ---------------------------------------------------------
CalcGcd PROC
; Description: Calculates the greatest common divisor between two values
; Receives: EBX = user value one, EAX = user value two
; Returns: EAX = Greatest common divisor
; ----------------------------------------------------------
	mov edx, 0
	xchg eax, ebx	; set eax as the dividend (x val)
	
L1:
	div ebx
	xchg eax, ebx
	mov ebx, edx

	cmp ebx, 0
	mov edx, 0
	je endDoWhile
	jmp L1
	
endDoWhile:
	ret
CalcGcd ENDP



; ---------------------------------------------------------
DisplayGcd PROC
; Description: Displays the GCD of the two values
; Receives: EAX = Greatest common divisor
; Returns: Nothing
; ----------------------------------------------------------

	mov edx, OFFSET resultPrompt
	call WriteString
	call WriteDec
	call Crlf
	call WaitMsg	
	call Crlf

	ret
DisplayGcd ENDP

END main