;seccion de variables
segment .data
  cont db '0' ; se reserva un byte de enters
  enters db 0xA
segment .text
global _start
_start:

  jmp loopi

loopi:
  cmp byte [cont], ':'
  jne incr
  je fin
fin:
  mov eax,1
  int 0x80
incr:
  ;imprime incremento
  mov edx,1
  mov ecx,cont
  mov ebx,1
  mov eax,4 ; 4 es para escribir
  int 0x80
  ;imprime enter
  mov edx,1
  mov ecx,enters
  mov ebx,1
  mov eax,4 ; 4 es para escribir
  int 0x80
  inc byte [cont]
  jmp _start
  int 0x80
