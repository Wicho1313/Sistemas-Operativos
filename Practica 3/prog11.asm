
segment .data

section .bss
  s1 resb 100
  espDigito resb 100
  posDigito resb 8


segment .text
global _start
_start:
    mov edx, 100d
    mov ecx,s1
    mov ebx,0
    mov eax,3
    int 0x80

    mov rdi,s1

    call len

    sub rax,1

    call imprimir

    mov rax, 60
    mov rdi, 0
    syscall


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

len:
  xor   rcx, rcx ;limpiar
siguiente:
  cmp   [rdi], byte 0  ;fin de cadena
  jz    salir
  inc   rcx
  inc   rdi
  jmp   siguiente
salir:
  mov   rax, rcx      ; guardar en rax
  ret                  ; salir
