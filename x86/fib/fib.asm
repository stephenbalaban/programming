;; Data section
section .data
	N	dd	33
	result	dd	0


;; Code Section
section .text
	global main
	extern printf

;; Iterative Fibonacci sequence
;; R = F_{n-1} + F_{n-2}
;; 1, 1, 2, 3, 5, 8, ...
main:
	mov eax, 0		; N-1
	mov ebx, 1		; N-2
	mov esi, [N]		; i
	loop:
		mov ecx, eax	; Copy N-1 into a temp register
		add eax, ebx	; Add N-2, N-1, store in N-1
		mov ebx, ecx	; Copy temp into N-2
		dec esi
		jnz loop

	; printf("F(%d) = %d\n", N, [eax])
	push eax
	push dword [N]
	push format_string
	call printf
	add esp, 4*3

	mov eax, 0
	ret


format_string:
	db	"F(%d) = %d", 0x0a, 0	; note 0x0a is newline, 0 is null terminated string
