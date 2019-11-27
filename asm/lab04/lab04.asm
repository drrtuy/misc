SECTION .data
    prompt1:     DB 'Полдень наступил?',10
    prompt1Len:  EQU $-prompt1
    prompt2:    DB 'Доброе утро',10
    prompt2Len: EQU $-prompt2
    prompt3:    DB 'Добрый день',10
    prompt3Len: EQU $-prompt3

SECTION .bss
buf1:   RESB 1

SECTION .text
GLOBAL _start

_start:
repeat: 
    mov rax,4 ; Initial prompt output to stdout
    mov rbx,1
    mov rcx,prompt1
    mov rdx,prompt1Len
    int 80h

    mov rax,3 ; Read from stdin
    mov rbx,0
    mov rcx,buf1
    mov rdx,1
    int 80h
    
    mov rdx,'n' ; Compare the input with y and n
    cmp rdx,[buf1]
    jz  noon
    mov rdx,'y' 
    cmp rdx,[buf1]
    jz  morn
    jmp repeat ; Repeat the process if input isn't y or n

noon:
    mov rax,4 ; Aux prompt output to stdout
    mov rbx,1
    mov rcx,prompt2
    mov rdx,prompt2Len
    int 80h
    jmp exit

morn:
    mov rax,4 ; Aux prompt output to stdout
    mov rbx,1
    mov rcx,prompt3
    mov rdx,prompt3Len
    int 80h

exit:
    mov rax,1 ; exit 0
    mov rbx,0
    int 80h
