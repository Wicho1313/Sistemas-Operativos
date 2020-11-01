
segment .data
  salto db 0xa
  d db '                                                                                       '
section .bss
  laux resb 1
  l4 resb 1
  s1 resb 50
  dr resb 500
  espDigito resb 100
  posDigito resb 8
  aux resb 500


segment .text
global _start
_start:
  mov edi,d
  mov edx, 50
  mov ecx,s1
  mov ebx,0
  mov eax,3
  int 0x80
  mov esi,s1
  call buscarfin

  times 9 call guardar

  mov rdi,d

  call len
  ;add rax,1
  ;add rax,2
  mov [l4],rax
  mov [laux],rax
  push laux

  call imprimir

  mov edx,[laux]
  mov ecx,d
  mov ebx,1
  mov eax,4 ; 4 es para escribir
  int 0x80

  mov edx,1
  mov ecx,salto
  mov ebx,1
  mov eax,4 ; 4 es para escribir
  int 0x80

  ;mov eax,l4
  call inverso


  mov edx,[laux]
  mov ecx,dr
  mov ebx,1
  mov eax,4 ; 4 es para escribir
  int 0x80

  mov edx,1
  mov ecx,salto
  mov ebx,1
  mov eax,4 ; 4 es para escribir
  int 0x80


  mov eax ,1
  int 0x80

guardar:
  mov edx, 50
  mov ecx,s1
  mov ebx,0
  mov eax,3
  int 0x80
  mov esi,s1
  inc edi
buscarfin:

  cmp   [esi], byte 0xa  ;fin de cadena
  jz    fin
  ;inc   esi
  mov ecx, 1
  rep movsb
  ;inc edi
  jmp   buscarfin
len:
  xor   rcx, rcx ;limpiar
siguiente:
  cmp   [rdi], byte ' '  ;fin de cadena
  jz    salir
  inc   rcx
  inc   rdi
  jmp   siguiente
salir:
  mov   rax, rcx      ; guardar en rax
  ret                  ; salir
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
inverso:
  mov esi,d
  sub esi,1
invimprimir:
  cmp [esi],byte 0
  jz  invfin
  mov edi,dr
  add edi,[laux]
  mov ecx,1
  rep movsb
  sub byte [laux],1
  jmp invimprimir
invfin:
  ret
fin:
  sub edi,1
  ret
