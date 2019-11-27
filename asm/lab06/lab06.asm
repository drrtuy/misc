; lab06
SECTION .data
    prompt1:     DB 'Введите символ',10
    prompt1Len:  EQU $-prompt1
    buf_converted:   DB 10,10,10,10 ; Max 3 decimal digits
    space_sign: DB 32

SECTION .bss
buf1:   RESB 1

SECTION .text
GLOBAL _start

print:
    ; TODO push string and length as args
    mov rax,4 ; Initial prompt output to stdout
    mov rbx,1
    int 80h
    ret

convert:
    xor rcx,rcx ; empty the register
    xor rbx,rbx ; empty the register
    mov bl,10 ; decimal base
.divide:
    xor rdx,rdx ; empty the register
    div rbx ; divide the number by the base
    
    add rdx,'0' ; sup 0 hex code and the remainder up
    push rdx ; save the digit ASCII code 
    
    inc rcx ; inc the digits counter 
    cmp rax,0 ; 
    jnz .divide
    
    mov rdi,buf_converted ; for stosb
    mov rdx,4 ; for stosb
    mov rbx,rcx ; copy digits counter for later usage

.reverse:
    pop rax ; pop up the digit ASCII code
    stosb ; put AL into a buffer
    dec rcx ; dec digit counter 
    cmp rcx,0
    jnz .reverse
    ret ; rbx contains a number of digits to print out

_start:
    ; TODO push args into a stack 
    mov rcx,prompt1
    mov rdx,prompt1Len
    call print

    mov rax,3 ; Read from stdin
    mov rbx,0
    mov rcx,buf1
    mov rdx,1
    int 80h

    mov rcx,buf1 ; print the char
    mov rdx,1
    call print

    mov rcx,space_sign ; print the space
    mov rdx,1
    call print

    xor rax,rax ; empty rax
    mov rax,[buf1] ; put a byte into AL
    call convert

    mov rcx,buf_converted ; put decimal digit code into a buffer
    inc rbx ; add extra byte for '\n'
    mov rdx,rbx ; digits counter
    call print
 
    mov rax,1 ; exit 0
    mov rbx,0
    int 80h
