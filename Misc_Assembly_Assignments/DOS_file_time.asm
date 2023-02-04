; Program: DOS_file_time
;
; Description: Takes a hex value as user input and converts it into a DOS File Time output
;			   sequence and prints it to STDOUT.

INCLUDE Irvine32.inc

.data
; output strings
promptUserInput BYTE 'Please enter 16-bit hexadecimal (4-digit, e.g., 1207): ', 0
outputBinary BYTE 'Your equivalent binary is ', 0
outputDOSTime BYTE 'Your DOS file time is ', 0
errorPrompt BYTE 'Error, invalid input: ', 0

; max comparison values for hours, minutes, and seconds
maxHours = 25
maxMinutes = 61
maxSeconds = 61

; bit mask values used to isolate hours, mins, and seconds
hoursMask  = 0F800h		; bits 11-15 = 1
minutesMask = 007E0h	; bits 5-10 = 1
secondsMask = 01Fh		; bits 0-4 = 1

.code
main PROC
	; clear registers
	mov eax, 0
	mov ebx, 0
	mov edx, 0

	call GetUserInput
	call ShowFileTime
	call WaitMsg

	exit
main ENDP



;-------------------------------------------
GetUserInput PROC
; Descripton: Prompts user and gets hex input
; Receives: Nothing
; Returns: Nothing
;-------------------------------------------
    
	; prompt for user input
	mov edx, offset promptUserInput
	call WriteString

	; clear eax and get user input
	mov eax, 0
	call ReadHex

	ret
GetUserInput ENDP



;-------------------------------------------
ShowFileTime PROC
; Description: Converts hex input and outputs it as a DOS file time sequence
; Receives: Nothing
; Returns: Nothing
;-------------------------------------------
	
	; output the binary equivalent of hex input
	mov edx, offset outputBinary
	call WriteString
	mov ebx, 2
	call WriteBinB

	; use ebx as placeholder for original hex input
	mov ebx, eax

	; output prompt for DOS time
	call Crlf
	mov edx, offset outputDOSTime
	call WriteString

	; convert hex value for hours into proper output format
	and eax, hoursMask		; isolate hours bits
	shr eax, 11				; shift hours bits into 0-4 for decimal output

	; check hours for proper range
	mov edx, maxHours
	call ValidateInput
	jc EXIT_PROGRAM

	; output the hours data
	call PrintZero
	call WriteDec
	mov al, ':'
	call WriteChar

	; convert hex value for minutes into proper output format
	mov eax, ebx			; move original input back to eax
	and eax, minutesMask	; isolate minutes bits
	shr eax, 5				; shift minutes bits to 0-4 for decimal output

	; check minutes for  proper range
	mov edx, maxMinutes
	call ValidateInput
	jc EXIT_PROGRAM
	 
	; output the minutes data
	call PrintZero
	call WriteDec
	mov al, ':'
	call WriteChar

	; convert hex value for seconds into proper output format
	mov eax, ebx			; move original input back to eax
	and eax, secondsMask	; isolate seconds bits
	shl eax, 1				; account for 2 second increments, shift left for decimal output

	; check seconds for proper range
	mov edx, maxSeconds
	call ValidateInput
	jc EXIT_PROGRAM

	; output the seconds data
	call PrintZero
	call WriteDec
     
EXIT_PROGRAM:
	call Crlf
	ret

ShowFileTime ENDP



;-----------------------------------
ValidateInput PROC uses eax edx
; Description: Tests that values are in proper time ranges
; Receives: Nothing
; Returns: Nothing
;-----------------------------------
	; compare value, if less than value it's valid, jump to clear flag
	cmp eax, edx
	jb valid

	; else, the input was invalid, display error
	call Crlf
	mov edx, offset errorPrompt
	call WriteString

	jmp return
	
valid: 
	clc
return: 
	ret

ValidateInput ENDP



;-----------------------------------
PrintZero PROC
; Description: Checks for and prints a leading zero if it is needed for output
; Receives: Nothing
; Returns: Nothing
;-----------------------------------
	; check if a leading zero is necessary
	cmp ax, 0Ah         
	ja return

	; if so, output a zero
	mov edx, eax
	mov eax, '0'
	call WriteChar
	mov eax, edx

return: 
	ret
PrintZero ENDP
END main