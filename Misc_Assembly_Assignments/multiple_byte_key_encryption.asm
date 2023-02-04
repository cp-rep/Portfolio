; Program:     multiple_byte_key_encryption
; Description: This program demonstrates simple symmetric-key encryption using the XOR instruction
;			   with a multi-byt ekey entered by the user.

INCLUDE Irvine32.inc

; symbolic constants
BUFMAX = 128

.data
prompt1		BYTE "Enter the plain text: ", 0
prompt2		BYTE "Enter the encryption key: ", 0
sEncrypt	BYTE "Cipher text: ", 0
sDecrypt	BYTE "Decrypted: ", 0

keyStr		BYTE BUFMAX+1 DUP(0)
keySize		DWORD ?
buffer		BYTE BUFMAX+1 DUP(0)
bufSize		DWORD ?
count		BYTE 0

.code
main PROC

	; clear register values
	mov eax, 0
	mov ebx, 0
	mov ecx, 0
	mov edx, 0

	; prompt enter text message to stdout
    mov		edx, OFFSET prompt1
	call	WriteString
	
	; get the message to encrypt from user
	mov		edx, OFFSET buffer
	mov		ecx, BUFMAX
	call	ReadString
	mov		bufSize, eax			; save length of user input
	call	Crlf

	;  prompt enter encryption key message to stdout
	mov		edx, OFFSET prompt2
	call	WriteString

	; get encryption key from user
	mov		edx, OFFSET keyStr
	mov		ecx, BUFMAX
	call	ReadString
	mov		keySize, eax			; save the key length
	call Crlf

	; use the keyStr to encrypt message
	call TranslateBuffer

	; prompt show cipher text to stdout
	mov		edx, OFFSET sEncrypt
	call	WriteString

	; show encrypted message to stdout
	mov		edx, OFFSET buffer
	call	WriteString
	call	Crlf
	call	Crlf

	; prompt show decrypted message to stdout
	mov edx, OFFSET sDecrypt
	call WriteString
	
	; use keyStr to decrypt message
	call TranslateBuffer

	; display decrypted message to stdout
	mov edx, OFFSET buffer
	call WriteString
	call Crlf

	exit
main ENDP

; ------------------------------------------------------
TranslateBuffer PROC
;
; Translates the string by exclusive-Oring each byte
; with the encryption key byte.
; Receives: nothing
; Returns: nothing
; ------------------------------------------------------
	mov		ecx, bufSize				; loop counter
	mov		esi, OFFSET buffer			; index 0 in buffer 
	mov		edi, OFFSET keyStr
	mov		count, 0

L1:
	mov		al, [esi]
	mov		bl, [edi]
	xor		al, bl						; translate byte
	mov		[esi], al
	inc		esi							; point to next byte
	inc		edi							; point to next key byte
	inc		count

	; if all bytes in key used up, reset to first byte
	mov edx, DWORD PTR count
	cmp edx, keySize
	JNE		NEXT
	mov count, 0
	mov edi, OFFSET keyStr

	; else, continue looping
	NEXT:
	loop	L1
	ret
TranslateBuffer ENDP
END main