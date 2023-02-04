Comment !
Description: Write a procedure named PackedToAsc that converts a
4-byte packed decimal number to a string of ASCII decimal digits.
Pass the packed number to the procedure in EAX, and pass a pointer
to a buffer that will hold the ASCII digits. Write a short test
program that demonstrates several conversions and displays the
converted numbers on the screen.
!

INCLUDE Irvine32.inc

.data
numbers DWORD 87654321h, 45346894h, 193492h, 123h, 3h
buffer BYTE 8 DUP(1), 0   ; 8 digits plus null character

.code
main PROC
	
   ; Prepare for LOOP
   mov esi, OFFSET numbers
   mov ecx, LENGTHOF numbers

L1:
   ; Prepare the pointer to buffer and a packed decimal number
   mov ebx, OFFSET buffer
   mov eax, [esi]

   ; Call _PackedToAsC to convert to ASCII digits
   call _PackedToAsC

   ; Display string of digits
   call WriteString
   call Crlf

   ; Get next number
   mov esi, TYPE numbers

   loop L1

   exit
main ENDP

;----------------------------------------------------------------
_PackedToAsc PROC uses ecx ebx
;
; procedure that converts a 4-byte packed decimal number
; to a string of ASCII decimal digits
; Receives: EAX, One packed decimal number
;           EDX, The pointer to a buffer with ASCII returned
; Returns: String of ASCII digits in buffer pointed by EDX
;------------------------------------------------------------------

	; initialize a counter for number of digit conversions
	mov esi, SIZEOF buffer - 1

	; convert digits
L1:
	mov		al, BYTE PTR numbers[esi]
	or		al, 30h
	mov		BYTE PTR [ebx], al
	inc		ebx
	mov		al, 0

	loop L1

	ret
_PackedToAsc ENDP


END main