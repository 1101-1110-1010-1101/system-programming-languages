section .text

string_length:
    xor rax, rax
string_length_loop:
    cmp byte [rdi+rax], 0
    je string_length_ret
    inc rax
    jmp string_length_loop
string_length_ret:
    ret

print_string:
    push rdx
    xor rax, rax
    call string_length
    mov rsi, rdi
    mov rdx, rax
    mov rax, 1
    mov rdi, 1
    syscall
    pop rdx
    ret


print_char:
    mov rax, 1
    push rdi
    mov rdi, 1
    mov rsi, rsp
    mov rdx, 1
    syscall
    add rsp, 8
    ret


print_newline:
    xor rax, rax
    ret

print_uint:
    push r12
    push r13
    mov r12, rsp
    mov rax, rdi
    mov r13, 10     ; radix, dont forget to restore r13
    dec rsp         ; dynamic bufer generation
    mov byte [rsp], 0
uint_loop:
    xor rdx, rdx    ; clear rdx, because div uses rdx:rax
    div r13
    add rdx, 0x30   ; because of ascii
    dec rsp         ; dynamic bufer generation
    mov [rsp], dl
    cmp rax, 0         ; when chastnoe is 0, then it`s time to bye-bye from loop
    je uint_ret
    jmp uint_loop
uint_ret:
    mov rdi, rsp
    call print_string
    mov rsp, r12
    pop r13
    pop r12
    ret

print_int:
    xor rax, rax
    test rdi, rdi
    js negative
    call print_uint
    jmp int_ret
negative:
    push rdi
    mov rdi, '-'
    call print_char
    pop rdi
    neg rdi
    call print_uint
int_ret:
    ret
string_equals:
    xor rax, rax
    ret


read_char:
    xor rax, rax
    mov rax, 0
    mov rdi, 0
    mov rdx, 1
    dec rsp
    mov rsi, rsp
    syscall
    test rax, rax     ; rax = number of characters read, if rax = 0, it's the end of input
    je print_char_ret
    xor rax, rax
    mov al, [rsp]
print_char_ret:
    inc rsp
    ret

read_word:
    push r13
    push r14
    xor r14, r14
    mov r10, rsi
    mov r13, rdi
first_loop:
    call read_char
    cmp al, 0x20
    jne write_char
    jmp first_loop
cont_read:
    call read_char
    cmp r14, r10
    je read_out
    cmp al, 0x20 ; space
    je read_ret
write_char:
    cmp al, 0x9 ; tab
    je read_ret
    cmp al, 0x0 ; end of input
    je read_ret
    mov byte [r13+r14], al
    inc r14
    jmp cont_read
read_ret:
    mov rax, r13
    mov byte [r13+r14], 0
    mov rdx, r14 ; string length
    pop r14
    pop r13
    ret
read_out:
    mov rax, 0
    xor rdx, rdx ; string length = 0
    pop r14
    pop r13
    ret

parse_uint:
    xor rax, rax
    ret

; rdi points to a string
; returns rax: number, rdx : length
parse_int:
    xor rax, rax
    ret 


string_copy:
    xor rcx, rcx
string_copy_loop:
    cmp rcx, rdx
    je string_copy_ret
    mov rax, [rdi+rcx]
    mov [rsi+rcx], rax
    inc rcx
    jmp string_copy_loop
string_copy_ret:
    ret
