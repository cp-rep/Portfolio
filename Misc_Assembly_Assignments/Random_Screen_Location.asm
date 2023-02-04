; Program:     random_screen_location
; Description: Get random screen row and column numbers, then in a loop display a character to those random locations

INCLUDE Irvine32.inc

count = 100

.data
	rows BYTE ?
	cols BYTE ?
	anyKeyPrompt BYTE "Press any key to continue...", 0

.code
main PROC
	mov eax, 0
	mov edx, 0
	mov ecx, count

	; get row and column range for output
	call GetMaxXY
	mov rows, al
	mov cols, dl

	L1:
		; get random row value
		call RandomRange
		mov dh, al

		;get random column value
		mov al, cols
		call RandomRange
		mov dl, al
		
		; move cursor to row/col
		call Gotoxy

		; write character to output
		mov al, 'A'
		call WriteChar

		; delay before next output
		mov eax, 250
		call Delay

		loop L1

	; reposition cursor at top left of output
	mov dh, 0
	mov dl, 0
	call Gotoxy

	; prompt press anykey to output
	mov edx, OFFSET anyKeyPrompt
	call WriteString

	; read a character from the user to close program
	call ReadChar
	mov rows, al

	exit
main ENDP

END main