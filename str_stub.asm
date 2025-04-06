BITS 64
global _start

section .text

;; RAX - src
;; RCX - until
shift_stack:
	; xor rcx, rcx
	; mov cl,  6
	push rax

lop:
	mov rax, QWORD [rsp+0x8+rcx*0x8]
	mov QWORD [rsp+0x18+rcx*0x8], rax
	dec cl
	test cl, cl
	jne lop
	pop rax
	ret


stub:
	push rbp
	mov rbp, rsp

	push rax
	push rcx

	push QWORD [rsp+0x28]
	push QWORD [rsp+0x28]

	mov cl, 6		; on stack in between
	call shift_stack
	add rsp, 0x10	; shift

	

	int3

_start:
	mov rax, 1
	mov rbx, 0x10
	push QWORD 0xdead
	push QWORD 0xcadd
	call stub
	int3