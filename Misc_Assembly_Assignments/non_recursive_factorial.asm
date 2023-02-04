Comment !
Description: Write a nonrecursive version of the Factorial procedure
(Section 8.5.2) that uses a loop. Write a short program that
interactively tests your Factorial procedure. Let the user enter
the value of n. Display the calculated factorial.
!

INCLUDE Irvine32.inc

.data
msgInput BYTE "Enter the value of n to calculate " 
   BYTE "the factorial (-1 to quit): ",0
msgOutput BYTE "The factorial is: ",0
factorialError  BYTE "Error: Result does not fit "
   BYTE "in 32 bits.",0

.code
main PROC
	; clear registers
	mov eax, 0
	mov ebx, 0
	mov edx, 0

L1:
	; message to display
	mov edx, OFFSET msgInput        ; message to display
	call WriteString
	call ReadInt                    ; get an integer n from the user
	jo Done                         ; If invalid input, jmp to Done. Try again.
	   
	; if n is -1, go quit
	cmp eax, -1d
	je quit

	call _FactorialIterative
	jc ERROR

	mov edx, OFFSET msgOutput
	call WriteString
	call WriteDec

	jmp Done
ERROR:
	mov edx, OFFSET factorialError
	call WriteString

Done:
	; go back to L1
	call crlf
	loop L1

quit: 
	call WaitMsg
	exit
main ENDP



;---------------------------------------------------
_FactorialIterative PROC
;
; Calculates a factorial nonrecursively
; Receives: eax = value of n to calculate factorial
; Returns: eax = calculated factorial
;---------------------------------------------------	
	; init
	mov ebx, eax

	; test if eax is 0.  if not zero, calculate factorial
	cmp eax, 0
	jne Factorial_Loop

	; if zero, return 1
	mov eax, 1
	jmp end_factorial

Factorial_loop:
	dec ebx
	clc
	cmp ebx, 0
	je end_factorial

	mul ebx
	jc end_factorial

	jmp Factorial_loop

end_factorial:
	ret

_FactorialIterative ENDP
END main