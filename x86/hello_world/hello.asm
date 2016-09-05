;; Data section
section .data
	x	dd	1293
	y	dd	5812

	N	dd	2	; divisor for AVG
	avg	dq	0


;; Code Section
section .text
	global main
	extern printf

main:
	mov eax, [x]
	mov ecx, eax		; copy eax to ecx for later printing
	mov ebx, [y]
	add eax, ebx

	; Take the average of the values
	fild	dword [x]
	fild	dword [y]
	fadd
	; st0 contains x + y
	fild	dword [N]	; load 2 into st1
	fdiv
	fstp	qword [avg]


	; push them in reverse order (printf pops until done.)
	push eax		; eax = x + y = 7
	push dword [y]
	push dword [x]

	; push the two parts of a 32-bit floatingpoint 
	push dword [avg+4]
	push dword [avg]

	push format_string
	call printf
	add esp, 4*6		; we need to add 16 bytes to the esp
				; 4 bytes for each push (including call)
				; and 8 bytes for the float
	ret			; pops from call


format_string:
	db	"AVG=%.2f %d + %d = %d", 0x0a, 0	; note 0x0a is newline
