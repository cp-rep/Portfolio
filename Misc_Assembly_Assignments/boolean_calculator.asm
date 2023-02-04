; Program:     boolean_calculator
; Description: Perform simple boolean calculations based on user hexidecimal input

INCLUDE Irvine32.inc

.data
msgMenu BYTE "---- Boolean Calculator ----------",0dh,0ah
	BYTE 0dh,0ah
	BYTE "1. x AND y"     ,0dh,0ah
	BYTE "2. x OR y"      ,0dh,0ah
	BYTE "3. NOT x"       ,0dh,0ah
	BYTE "4. x XOR y"     ,0dh,0ah
	BYTE "5. Exit program",0

prompt1 BYTE "Exiting program", 0dh, 0ah, 0

msgAND BYTE "Boolean AND",0
msgOR  BYTE "Boolean OR",0
msgNOT BYTE "Boolean NOT",0
msgXOR BYTE "Boolean XOR",0

msgOperand1 BYTE "Input the first 32-bit hexadecimal operand:  ",0
msgOperand2 BYTE "Input the second 32-bit hexadecimal operand: ",0
msgResult   BYTE "The 32-bit hexadecimal result is:            ",0

caseTable BYTE '1'   ; lookup value
	DWORD _AND_op
	entrySize = ($ - caseTable)
	BYTE '2'
	DWORD _OR_op
	BYTE '3'
	DWORD _NOT_op
	BYTE '4'
	DWORD _XOR_op
	BYTE '5'
	DWORD _ExitProgram

numberOfEntries = ($ - caseTable) / entrySize

.code
main08stub PROC
	; clear registers
	mov eax, 0
	mov ebx, 0
	mov edx, 0

	; Show menu in a loop
Menu:
	mov edx, OFFSET msgMenu
	call WriteString
	call crlf

	; get user input
	newChar:
		call ReadChar

	; verify the input
	testOne: 
		mov dl, 30h
		cmp al, dl
		jnc testTwo

	testTwo:
		mov dl, 36h
		cmp al, dl
		jc validInput

		; loop back to read a new character if the input was invalid
		jmp newChar

	; else, the input was valid, continue call to appropriate procedure	
	validInput:
		; preventative carry clear
		clc
		call _ChooseProcedure

		; successfully called procedure, check if user exited program
		jc exitProgram

		; otherwise, repeat program
		jmp Menu

	exitProgram:
		exit
main08stub ENDP



;------------------------------------------------
_ChooseProcedure PROC
;
; Description: Selects a procedure from the caseTable
; Receives: AL is the number of operation the user entered
; Returns: if CF set, exit; else continue 
;------------------------------------------------
	mov ecx, numberOfEntries
	mov esi, offset caseTable

	; call procedure based on input
	L1:
		cmp al, [esi]
		je callProc    
		add esi, EntrySize
		loop L1
		jmp endChooseProc
	callProc:
		call crlf
		call near ptr [esi + 1]
	
	endChooseProc:  
		ret
_ChooseProcedure ENDP



;------------------------------------------------
_AND_op PROC
;
; Description: Performs a boolean AND operation
; Receives: Nothing
; Returns: Nothing
;------------------------------------------------
	mov edx, OFFSET msgAND
	call WriteString
	call Crlf
	call Crlf

	; get hex values and display operation results
	call _GetHexValue
	AND ebx, edx
	call _PrintResult
	ret
_AND_op ENDP



;------------------------------------------------
_OR_op PROC
;
; Description: Performs a boolean OR operation
; Receives: Nothing
; Returns: Nothing
;------------------------------------------------
	mov edx, offset msgOR
	call WriteString
	call Crlf
	call Crlf

	; get hex values and display operation results
	call _GetHexValue
	OR ebx, edx
	call _PrintResult
	ret
_OR_op ENDP



;------------------------------------------------
_NOT_op PROC
;
; Description: Performs a boolean NOT operation.
; Receives: Nothing
; Returns: Nothing
;------------------------------------------------
	mov edx, offset msgNOT
	call WriteString
	call Crlf
	call Crlf

	; get hex value
	mov edx, offset msgOperand1
	call WriteString
	call ReadHex
	mov ebx, eax
    clc

	; perform not on data and display
	NOT ebx
	call _PrintResult

	ret

_NOT_op ENDP



;------------------------------------------------
_XOR_op PROC
;
; Description: Performs an Exclusive-OR operation
; Receives: Nothing
; Returns: Nothing
;------------------------------------------------
	mov edx, offset msgXOR
	call WriteString
	call Crlf
	call Crlf

	; get hex values and display operation results
	call _GetHexValue
	XOR ebx, edx
	call _PrintResult 
	ret
_XOR_op ENDP



;------------------------------------------------
_GetHexValue PROC
;
; Description: Gets a hex value from the user for an operation
; Receives: Nothing
; Returns: Nothing
;------------------------------------------------

	; get first hex value
	mov edx, offset msgOperand1
	call WriteString
	call ReadHex
	mov ebx, eax

	; get second hex value (if needed)
	mov edx, offset msgOperand2
	call WriteString
	call ReadHex
	mov edx, eax

	ret
_GetHexValue ENDP



;------------------------------------------------
_PrintResult PROC
; Description: Displays results of boolean calculation
; Receives: Nothing
; Returns: Nothing
;------------------------------------------------
	mov edx, offset msgResult
	call WriteString
	mov eax, ebx
	call WriteHex
	call Crlf
	call Crlf
	ret
_PrintResult ENDP



;------------------------------------------------
_ExitProgram PROC
; Description: If called, sets the CF = 1
; Receives: Nothing
; Returns: Sets CF = 1 to signal end of program
;------------------------------------------------
	; set carry flag signaling user wants to exit program
	stc
	ret
_ExitProgram ENDP

END main08stub