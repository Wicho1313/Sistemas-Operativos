
segment .data
  intro db 'Elige el numero de la operacion a realizar y posteriormente introduce los dos numeros',10
  introl equ ($-intro)
  opc db '1) Suma 2)Resta 3)Division 4)Multiplicacion',10
  opcl equ ($-opc)

  nega db '-'
  negal equ ($-nega)

  suma db 'Suma',10
  sumal equ ($-suma)

  salto db 0xa
section .bss
  opcion resb 2
  num1 resb 50
  num2 resb 50
  espDigito resb 100
  posDigito resb 8

segment .text
global _start
_start:
    mov edx,introl
    mov ecx, intro
    mov ebx,1
    mov eax,4
    int 0x80

    mov edx,opcl
    mov ecx,opc
    mov ebx,1
    mov eax,4
    int 0x80

    mov edx,2
    mov ecx,opcion
    mov ebx,0
    mov eax,3
    int 0x80


    mov edx,50
    mov ecx,num1
    mov ebx,0
    mov eax,3
    int 0x80

    mov edx,50
    mov ecx,num2
    mov ebx,0
    mov eax,3
    int 0x80

    sub byte [opcion],'0'
    cmp byte [opcion],byte 1
    je sum
    cmp byte [opcion],byte 2
    je res
    cmp byte [opcion],byte 3
    je divi
    cmp byte [opcion],byte 4
    je multi


sum:

    mov rax, num1
    call atoi
    push rax

    mov rax, num2
    call atoi
    pop rdx
    add rax,rdx

    call imprimir

    mov eax,1
    int 0x80
res:
    mov rax, num1
    call atoi
    push rax

    mov rax, num2
    call atoi
    pop rdx
    cmp rax,rdx
    jg cambio

    sub rdx,rax

    mov rax, rdx
    call imprimir

    mov eax,1
    int 0x80
cambio:
    push rax
    push rdx

    mov edx,negal
    mov ecx,nega
    mov ebx,1
    mov eax,4
    int 0x80

    pop rdx
    pop rax

    sub rax,rdx
    call imprimir

    mov eax,1
    int 0x80
divi:
    mov rax, num1
    call atoi
    push rax

    mov rax, num2
    call atoi
    mov rbx,rax
    pop rax

    div rbx

    ;mov rax, rdx
    call imprimir

    mov eax,1
    int 0x80
multi:
    mov rax, num1
    call atoi
    push rax

    mov rax, num2
    call atoi
    mov rbx,rax
    pop rax

    mul rbx

    ;mov rax, rdx
    call imprimir

    mov eax,1
    int 0x80

atoi:
    mov     esi, eax        ; mueve puntero en eax a esi
    mov     eax, 0          ;inicializa con 0
    mov     ecx, 0

.potencia10:
    xor     ebx, ebx        ;limpia ebx
    mov     bl, [esi+ecx]   ; mueve el numero de bytes ecx
    cmp     bl, 48          ; compara con 48 (0 en ascii)
    jl      .finatoi       ; salta al final si es menor
    cmp     bl, 57          ;compara con 57 (9 en ascii)
    jg      .finatoi       ; salta al final si es mayor
    cmp     bl, 10          ; compara con enter
    je      .finatoi       ;  va al final si es igual
    cmp     bl, 0           ;compara con final de cadena
    jz      .finatoi       ; va al final si es 0

    sub     bl, 48          ; convierte el valor en entero
    add     eax, ebx        ; agrega el valor al numero
    mov     ebx, 10         ; mueve 10 a ebx
    mul     ebx             ; multiplica eax por ebx
    inc     ecx             ; incrementa ecx, numero de bytes
    jmp     .potencia10

.finatoi:
    mov     ebx, 10 ;divide entre 10 pues sobro una potencia de 10
    div     ebx
    ret


imprimir:
    mov rcx, espDigito
    mov rbx, 10
    mov [rcx], rbx
    inc rcx
    mov [posDigito], rcx

bucle:
    mov rdx, 0
    mov rbx, 10
    div rbx
    push rax
    add rdx, 48

    mov rcx, [posDigito]
    mov [rcx], dl
    inc rcx
    mov [posDigito], rcx

    pop rax
    cmp rax, 0
    jne bucle

bucle2:
    mov rcx, [posDigito]

    mov rax, 1
    mov rdi, 1
    mov rsi, rcx
    mov rdx, 1
    syscall

    mov rcx, [posDigito]
    dec rcx
    mov [posDigito], rcx

    cmp rcx, espDigito
    jge bucle2
    ret
