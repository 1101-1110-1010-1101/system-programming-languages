global _start
section .data
msg_noword: db "No such word",0

section .text
%include "colon.inc"

extern find_word
extern read_word
extern string_length
extern print_string
extern print_newline

_start:
	mov rsi, 255
	sub rsp, 256
	mov rdi, rsp
	call read_word
	test rax, rax
	jz .bad
	mov rdi, rax
	mov rsi, lw
	call find_word
	test rax, rax
	jz .bad
	add rax, 8
	mov r10, rax
	call string_length
	add r10, rax
	mov rdi, r10
	inc rdi
	call print_string
.exit:
	call print_newline
	mov rdi, rax
	mov rax, 60	; number 'exit'
	syscall
.bad:
	mov rdi, msg_noword
	call string_length
	mov rsi, rax
	call print_string
	jmp .exit


