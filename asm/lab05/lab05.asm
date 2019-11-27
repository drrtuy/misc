; lab05
SECTION .data
    prompt1:     DB 'Введите строку',10
    prompt1Len:  EQU $-prompt1

SECTION .bss
buf1:   RESB 42

SECTION .text
GLOBAL _start

_start:
    mov rax,4 ; Initial prompt output to stdout
    mov rbx,1
    mov rcx,prompt1
    mov rdx,prompt1Len
    int 80h

    mov rax,3 ; Read from stdin
    mov rbx,0
    mov rcx,buf1
    mov rdx,42
    int 80h
    
    xor rdx,rdx ; zeroing counter

repeatpush:
    movzx ax,byte [buf1+rdx] ; use a lower byte zeroing higher byte in AX
    push ax ; push AX into a stack
    inc rdx
    cmp ax,10
    jne repeatpush ; loop cond jump

    dec rdx ; to skip extra char taken with '/n'
    mov rcx,rdx ; copy counter
    xor rdx,rdx ; zeroing counter
    pop ax ; skiping '/n' from the stack

reverseit:
    pop ax ;
    mov byte[buf1+rdx],al ; copy a lower byte of popped AX
    inc rdx 
    cmp rdx,rcx ; consider only N chars put into the stack
    jne reverseit 

    mov rax,4 ; Put reversed input string to stdout
    mov rbx,1
    mov rcx,buf1
    mov rdx,42
    int 80h

    mov rax,1 ; exit 0
    mov rbx,0
    int 80h
