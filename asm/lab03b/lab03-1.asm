SECTION .data
    prompt1:     DB 'Введите строку',10
    prompt1Len:  EQU $-prompt1
    prompt2:    DB 'Введено',10
    prompt2Len: EQU $-prompt2

SECTION .bss
buf1:   RESB 80

SECTION .text
GLOBAL _start

_start:
    mov eax,4 ; Initial prompt output to stdout
    mov ebx,1
    mov ecx,prompt1
    mov edx,prompt1Len
    int 80h

    mov eax,3 ; Read from stdin
    mov ebx,0
    mov ecx,buf1
    mov edx,80
    int 80h

    mov eax,4 ; Aux prompt output to stdout
    mov ebx,1
    mov ecx,prompt2
    mov edx,prompt2Len
    int 80h

    mov eax,4 ; Output to stdout the contents of buf1
    mov ebx,1
    mov ecx,buf1
    mov edx,80
    int 80h

    mov eax,1 ; exit 0
    mov ebx,0
    int 80h
