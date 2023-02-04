; Program: Twos Compliment Shortcut

INCLUDE Irvine32.inc

.data
;userInput	SDWORD ?
testMASK SDWORD 1h
;result		SDWORD 0

; strings for output to STDOUT
userPrompt		BYTE "Enter a 32-Bit Signed Integer in Decimal: ", 0
hexPrompt		BYTE "Your integer input in hexadecimal is ", 0
twosHexPrompt	BYTE "The 2's compliment in hexadecimal is ", 0
twosDecPrompt	BYTE "The 2's compliment in decimal is ", 0

; Function Prototypes
; GetUserInput PROC
; ConvertTwosComp PROC
; OutputResult PROC

.code
main PROC
	; clear registers
	mov eax, 0
	mov ebx, 0
	mov edx, 0

	; get decimal value from user, output related info to STDOUT	
	call GetUserInput

	; if user enters 0, no conversion necessary
	cmp eax, 0
	je promptResult

	; else, convert user data into twos compliment
	call ConvertTwosComp
		
	promptResult:
		call OutputResult

	exit
main ENDP



;------------------------------------------------
GetUserInput PROC
;
; Description: Gets a decimal value from the user
; Receives: Nothing
; Returns: Nothing
;------------------------------------------------
	mov edx, OFFSET userPrompt
	call WriteString
	call ReadInt
	mov edx, OFFSET hexPrompt
	call WriteString
	mov ebx, TYPE DWORD
	call WriteHexB
	call Crlf
	mov ebx, eax
	ret
GetUserInput ENDP



; -----------------------------------------------
ConvertTwosComp PROC
; Description: moving from right to left, finds the first 1 bit,
;			   leaves it, and flips the remaining bits of that value	
; Receives: Nothing
; Returns: Nothing
; -----------------------------------------------
	
	; look for the first enabled bit in user input, break loop when found
	findFirstOne:
		mov eax, testMask
		test ebx, eax
		rol eax, 1
		jnz exitFindFirst
		jmp findFirstOne
		exitFindFirst:
		
	; flip the remaining bits in the value
	flipRemainingBits:
		XOR ebx, eax
		rol eax, 1
		cmp eax, 1
		je exitLoop

		jmp flipRemainingBits

		exitLoop:

	ret
ConvertTwosComp ENDP



; -----------------------------------------------
OutputResult PROC
; Description: Outputs the resulting twos compliment of the user input	
; Receives: Nothing
; Returns: Nothing
; -----------------------------------------------

	call Crlf
	mov edx, OFFSET twosDecPrompt
	call WriteString
	mov eax, ebx
	call WriteInt
	call Crlf
	call WaitMsg

	ret
OutputResult ENDP
END main