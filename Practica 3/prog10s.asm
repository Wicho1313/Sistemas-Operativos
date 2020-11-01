;seccion de variables

segment .data
  l1 dd 1
  l2 dd 1
  l3 dd 1
  l4 dd 1
  salto db 0xa
section .bss
  s1 resb 50
  s2 resb 50
  s3 resb 50
  d resb 150


segment .text
global _start
_start:
  mov edx, 50d
  mov ecx,s1
  mov ebx,0
  mov eax,3
  int 0x80
  mov edx, 50d
  mov ecx,s2
  mov ebx,0
  mov eax,3
  int 0x80
  mov edx, 50d
  mov ecx,s3
  mov ebx,0
  mov eax,3
  int 0x80

  mov edi,s1
  call _strlen
  mov [l1],eax
  mov [l4],eax
  mov edi,s2
  call _strlen
  mov [l2],eax
  add [l4],eax
  mov edi,s3
  call _strlen
  mov [l3],eax
  add [l4],eax

  mov eax,0
  xor edi,edi
  mov edi,d
  jmp cop1

modu:
  add eax,1
  cmp eax,[l4]
  jle cop1
  jmp final

cop1:
  cmp eax,[l1]
  jge cop2

  mov esi,s1
  add esi,eax
  mov ecx, 1
  rep movsb

cop2:
  cmp eax,[l2]
  jge cop3

  mov esi,s2
  add esi,eax
  mov ecx, 1
  rep movsb

cop3:
  cmp eax,[l3]
  jge modu

  mov esi,s3
  add esi,eax
  mov ecx, 1
  rep movsb


  jmp modu

final:
  mov edx,[l4]
  mov ecx,d
  mov ebx,1
  mov eax,4 ; 4 es para escribir
  int 0x80

  mov edx,1
  mov ecx,salto
  mov ebx,1
  mov eax,4 ; 4 es para escribir
  int 0x80

  mov eax,1
  int 0x80

;-----------------------

_strlen:
  mov   ebx, edi            ; rbx = rdi
  xor   al, al              ; limpiar al
  mov   ecx, 0xffffffff     ; maximo numero de bytes
  repne scasb               ; while [rdi] != al, sigue escaneando
  sub   edi, ebx            ; longitud = dist2 - dist1
  sub   edi,2
  mov   eax, edi            ; eax guarda la longitud
  ret                       ; volver
