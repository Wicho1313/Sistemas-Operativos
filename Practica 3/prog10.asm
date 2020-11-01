;seccion de variables

segment .data
  s1 db '1234'
  l1 EQU ($-s1)
  s2 db '2345'
  l2 EQU ($-s2)
  s3 db '3456'
  l3 EQU ($-s3)
  d db (l1+l2+l3)
  l4 EQU (l1+l2+l3)
  uno dw 1
  cont2: dw 0
  cont3: dw 0

section .bss

segment .text
global _start
_start:

  mov eax,0

  mov esi,s1     ; put address into the source index
  add esi,eax
  mov edi,d        ; put address into the destination index
  mov ecx, 1
  rep movsb


  push eax
  add word [esi],'0'
  mov edx,1
  mov ecx,[esi]
  mov ebx,1
  mov eax,4 ; 4 es para escribir
  int 0x80
  sub word [esi],'0'
  pop eax


  mov esi, s2     ; put address into the source index
  add esi,eax
  ;mov edi, d        ; put address into the destination index

  ;-----inc esi
  mov ecx, 1
  rep movsb

  push eax

  add word [edi],'0'
  mov edx,1
  mov ecx,[edi]
  mov ebx,1
  mov eax,4 ; 4 es para escribir
  int 0x80
  sub word [edi],'0'

  pop eax

  inc edi
  mov esi, s3     ; put address into the source index
  add esi,eax
  ;mov edi, d        ; put address into the destination index

  ;inc edi
  mov ecx, 1
  rep movsb

  push eax

  add word [edi],'0'
  mov edx,1
  mov ecx,[edi]
  mov ebx,1
  mov eax,4 ; 4 es para escribir
  int 0x80
  sub word [edi],'0'

  pop eax

  ;inc edi
  mov esi, s1     ; put address into the source index


  ;inc edi
  add eax,1 ;;esto solo se pone una vez xD


  add esi,eax
  mov ecx, 1
  rep movsb

  push eax

  add word [edi],'0'
  mov edx,1
  mov ecx,[edi]
  mov ebx,1
  mov eax,4 ; 4 es para escribir
  int 0x80
  sub word [edi],'0'

  pop eax

  ;---------------
  mov esi, s2
  add esi,eax
  mov ecx, 1
  rep movsb

  push eax

  add word [edi],'0'
  mov edx,1
  mov ecx,[edi]
  mov ebx,1
  mov eax,4 ; 4 es para escribir
  int 0x80
  sub word [edi],'0'

  pop eax


  mov edx,7
  mov ecx,d
  mov ebx,1
  mov eax,4 ; 4 es para escribir
  int 0x80
  mov eax,1
  int 0x80
