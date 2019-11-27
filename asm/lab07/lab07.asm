; lab07
SECTION .data
    prompt:    DB 'Введите строку',10
    prompt_len: EQU $-prompt
    result:     TIMES 17 DB '0'
    result_len: EQU $-result  

SECTION .bss
buf1:   RESB 42

SECTION .text
GLOBAL _start

_start:
    mov rax,4 ; Initial prompt output to stdout
    mov rbx,1
    mov rcx,prompt
    mov rdx,prompt_len
    int 80h

    mov rax,3 ; Read from stdin
    mov rbx,0
    mov rcx,buf1
    mov rdx,42
    int 80h

    xor rdx,rdx ; zero RDX
    xor r8,r8 ; empty the temp register
    xor r9,r9 ; empty the dest register
    xor rcx,rcx

next_symbol:
    movzx cx,byte [buf1+rdx] ; use a lower byte zeroing higher byte in AX
    inc rdx ; inc the symb counter
    call is_digit ; rbx=1 if char is a digit rbx=0 otherwise
    cmp rbx,0
    je check_4_newline

    ; The char is a digit thus setting an digit-th bit
    call set_bit ; set AL-th bit in R8 if this is digit
check_4_newline:
    cmp cx,10 ; the symb is newline
    jne next_symbol ; check the symbol again

breakpoint1:
    call reg_2_string

breakpoint2:
    mov rcx,result
    mov rdx,result_len 
    call print

exit:
    mov rax,1 ; exit 0
    mov rbx,0
    int 80h

is_digit: ; There is a digit in DL or not?
    xor rbx,rbx ; clean up RBX
    cmp cl, '0' ; if symbol ASCII code < '0'
    jb .notdigit 
    cmp cl, '9' ; if symbol ASCII code > '9'
    ja .notdigit
    mov rbx,1 ; this is digit
.notdigit:
    ret

set_bit:
    sub cl,'0' ; get the value of the digit in AL
    xor r8,r8 ; empty r8
    cmp cl,0 ; if digit is '0' then do nothing
    je .do_shift
    mov r8,1 ; left shift scrap place
    dec cl ; reduce the counter to set N-1-th bit
.do_shift:
    shl r8,cl ; shift left CL times 
    or r9,r8 ; combine bits
    ret

print:
    ; TODO push string and length as args
    mov rax,4 ; Initial prompt output to stdout
    mov rbx,1
    int 80h
    ret

reg_2_string: ; RCX where to put, RDX buf size, R9 src register
    mov cl,0 ; loop counter
    mov rdi,result ; calculate the end of result buf as result+result_len-1
    lea r13,[rdi+result_len] ; and put it into R13
    dec r13 ; newline address 
    mov byte [r13],10 ; put a newline
    dec r13 ; move to the 1st byte
.loop:
    xor r11,r11 ; empty r11
    mov r11,r9 ; put src register value to cmp bits
    mov r12,1 ; shift scrap
    shl r12,cl ; set CL-th bit(counting from 0) to 1
    and r11,r12 ; and src with the RAX-th bit
    cmp r11,0 
    je .next1 ; continue if RAX-th bit isn't set
    mov byte [r13],'1' ; print '1' otherwise
.next1:
    dec r13 ; move to a next byte of the result
    inc cl ; inc loop counter
    cmp cl,9 ; check loop boundary
    jb .loop

    ret    
