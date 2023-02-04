; Program:     Copy_a_string_Backwards
; Description: Copy a string of data into a new string in reverse order, then output the result

.386
.model flat,stdcall
.stack 4096
ExitProcess proto,dwExitCode:dword


INCLUDE Irvine32.inc
.data
original BYTE "This is the source string", 0
stringLength = ($ - original)			; get length of string to copy
reversed BYTE stringLength DUP(0)		; allocate space for a new string of same length

.code
main proc
	mov ecx, stringLength
	mov esi, OFFSET [original + (stringLength - 2)]		; point ESI to end address of original string
	mov edi, OFFSET [reversed]							; point EDI to beginning address of new string


	; loop and copy original string in reverse order to new string
	L1: 
		mov al, [esi]		
		mov [edi], al
		dec esi
		inc edi
		loop L1


	; output data to console
	mov edx, OFFSET original
	call WriteSTring					; output original string
	mov edx, OFFSET reversed
	call Crlf
	call WriteString					; output new string
	call Crlf
   invoke ExitProcess, 0
main endp
end main