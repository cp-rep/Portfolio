; Program:     print_fibonacci_until_overflow
; Description: this program calculates the highest value of fibonacci that can fit into a 
;				signed DWORD and outputs those values to STDOUT.  It also writes those values
;				to an array in a file.

INCLUDE Irvine32.inc

; symbolic constants
FIB_COUNT = 999
BUFSIZE = 188

.data
	fileHandle DWORD ?
	filename BYTE "fibonacci.bin", 0
	array DWORD FIB_COUNT DUP(?)		; initialize array of DWORD TYPE with 47 elements
	count	DWORD 1
	separate	BYTE ": ", 0

.code
main2sub PROC

	; Prepare ESI and ECX
	mov eax, 0
	mov edx, 0
	mov ebx, 1
	mov ecx, -1
	mov esi, OFFSET [array]

	; Call the Generate Fibonacci Procedure
	call generate_fibonacci

	; Create the output file
	mov edx, OFFSET filename
	call CreateOutputFile

	; Write array to file
	mov fileHandle, eax
	mov ecx, BUFSIZE
	mov edx, OFFSET array
	call WriteToFile

	; Close the file
	mov eax, fileHandle
	call CloseFile

	; call the wait message
	call WaitMsg

	exit
main2sub ENDP

; ---------------------------------------------------------------
generate_fibonacci PROC USES eax ebx ecx edx
;
; Generates fibonacci values and stores in an array.
; Receives: ESI points to the array
; Returns: nothing
; ---------------------------------------------------------------
	L1:

		; display count to stdout
		push eax
		mov eax, count
		call WriteDec
		mov edx, OFFSET separate
		call WriteString
		pop eax

		; calculate fibonacci
		mov [esi], ebx
		add eax, ebx
		xchg eax, ebx
		mov edx, ebx

		call WriteDec
		call Crlf
		add esi, 4
		inc count
		 
		cmp edx, 1836311903
		JA TOOBIG

		loop L1
		TOOBIG:
	ret
generate_fibonacci ENDP
END main2sub