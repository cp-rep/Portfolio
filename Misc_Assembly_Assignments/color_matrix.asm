; Program:     color_matrix
; Description: display a single character with all possible color combinations in a 16x16 grid using a single loop

INCLUDE Irvine32.inc

.data

.code
main PROC
	mov eax, 0
	mov edx, 0
	mov bl, 16d
	mov ebx, 16
	mov ecx, 256

	L1:
		; set color and write a char
		mov edx, eax
		call SetTextColor
		mov al, 'X'
		call WriteChar
		mov eax, edx

		; advance color
		inc al
	
		; check if 16 chars in a row
		cmp ebx, eax

		; if not, jump to next
		jne next

		; if yes, make a new line
		add ebx, 16
		call Crlf

		next:
		loop L1

		; prompt user input for exit
		mov eax, 0Fh
		call SetTextColor
		call Crlf
		call WaitMsg

	exit
main ENDP
END main