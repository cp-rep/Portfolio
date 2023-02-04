; Program: packed_bcd_to_ascii
; Description: This program converts hex values stored in memory to packed decimal integers
;				and temporarily stores them in a buffer, printing them to STDOUT

INCLUDE Irvine32.inc

.data
numbers DWORD 87654321h, 45346894h, 193492h, 123h, 3h
buffer BYTE 8 DUP(1), 0 ; 8 digits plus null character

.code
main PROC
	; clear registers
	mov		eax, 0
	mov		ebx, 0
	mov		ecx, 0
	mov		edx, 0

	; Prepare for LOOP
	mov		esi, OFFSET numbers
	mov		ecx, LENGTHOF numbers

L1:
	; Prepare the pointer to buffer and a packed decimal number
	mov		edx, OFFSET buffer
	mov		eax, [esi]

	; Call _PackedToAsC to convert to ASCII digits
	call	_PackedToAsC

	; Display string of digits
	call	WriteString
	call	Crlf

	; Get next value in numbers and loop
	add		esi, TYPE DWORD
	loop	L1

	call	WaitMsg

	exit
main ENDP



;----------------------------------------------------------------
_PackedToAsc PROC uses ecx edx
;
; procedure that converts a 4-byte packed decimal number
; to a string of ASCII decimal digits
; Receives: EAX, One packed decimal number
;           EDX, The pointer to a buffer with ASCII returned
; Returns: String of ASCII digits in buffer pointed by EDX
;------------------------------------------------------------------

	; initialize a counter for number of digit conversions
	mov		ecx, eax
L1: 
	; move first digit into bl
	shld	ebx, eax, 4         

	; rotate eax 1 full hex value
	rol		eax, 4 

	; convert the shifted hex value in BL to it's ASCII value
	or		bl, 30h

	; mov the converted value into the buffer
	mov		BYTE PTR [edx], bl

	; point ebx to next buffer byte
	inc		edx

	; set bl value to zero
	and		bl, 0
	 
	; test if ecx is equal to original value, if so, all values have been packed, then ret
	cmp		ecx,eax
	je		next

	; else, continue looping
	jmp		L1

next:
     ret
_PackedToAsc ENDP

END main