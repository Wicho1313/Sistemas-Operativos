;nasm -f win32 -o prog12.obj prog12.asm
;ld prog12.obj -m i386pe -e _start -L "C:\Users\luisg\Documents\SistemasOperativos\Practica 3" -l kernel32 -o prog12.exe
segment .data
  salto db 0xa
  d db '                                                                                       '
section .bss
caract resd 1
handleConsola resd 1
caractEscritos resd 1
longitudCadena resd 1
ultimoArgumento resd 1
  laux resb 1
  l4 resb 1
  s1 resb 50
  dr resb 500
  espDigito resb 100
  posDigito resb 8
  aux resb 500


segment .text
global _start
extern _GetStdHandle@4
extern _ReadConsoleA@20
extern _WriteConsoleA@20
extern _ExitProcess@4
_start:
  mov edi,d

  push dword -10
          call _GetStdHandle@4
          mov [handleConsola],eax
          xor eax,eax
          mov eax,50
          mov[longitudCadena],eax
          xor eax,eax
          mov eax,0d
          mov [ultimoArgumento],eax
          push dword [ultimoArgumento]
          push dword caractEscritos
          push dword [longitudCadena]
          push dword s1
          push dword [handleConsola]
          call _ReadConsoleA@20

  mov esi,s1
  call buscarfin

  times 2 call guardar

  mov edi,d

  call len
  ;add eax,1
  ;add eax,2
  mov [l4],eax
  mov [laux],eax
  push laux

  call imprimir

  push dword-11
  xor eax,eax;
  call _GetStdHandle@4;
  mov [handleConsola],eax;
  xor eax,eax;
  mov eax,0d;
  mov [ultimoArgumento],eax;
  push dword [ultimoArgumento];
  push dword caractEscritos;
  push dword 30;
  push dword d
  push dword [handleConsola];
  call _WriteConsoleA@20;

  push dword-11
  xor eax,eax;
  call _GetStdHandle@4;
  mov [handleConsola],eax;
  xor eax,eax;
  mov eax,0d;
  mov [ultimoArgumento],eax;
  push dword [ultimoArgumento];
  push dword caractEscritos;
  push dword 1;
  push dword salto
  push dword [handleConsola];
  call _WriteConsoleA@20;

  ;mov eax,l4
  call inverso


  push dword-11
  xor eax,eax;
  call _GetStdHandle@4;
  mov [handleConsola],eax;
  xor eax,eax;
  mov eax,0d;
  mov [ultimoArgumento],eax;
  push dword [ultimoArgumento];
  push dword caractEscritos;
  push dword 30;
  push dword dr
  push dword [handleConsola];
  call _WriteConsoleA@20;

  push dword-11
  xor eax,eax;
  call _GetStdHandle@4;
  mov [handleConsola],eax;
  xor eax,eax;
  mov eax,0d;
  mov [ultimoArgumento],eax;
  push dword [ultimoArgumento];
  push dword caractEscritos;
  push dword 1;
  push dword salto
  push dword [handleConsola];
  call _WriteConsoleA@20;


  xor eax,eax;
  mov eax,0d;
  mov [ultimoArgumento],eax;
  push dword [ultimoArgumento];
  call _ExitProcess@4;

guardar:
push dword -10
        call _GetStdHandle@4
        mov [handleConsola],eax
        xor eax,eax
        mov eax,50d
        mov[longitudCadena],eax
        xor eax,eax
        mov eax,0d
        mov [ultimoArgumento],eax
        push dword [ultimoArgumento]
        push dword caractEscritos
        push dword 50
        push dword s1
        push dword [handleConsola]
        call _ReadConsoleA@20
  mov esi,s1
  inc edi
  ;dec edi
  ;dec edi
buscarfin:

  cmp   [esi], byte '*'  ;fin de cadena
  jz    fin
  ;inc   esi
  mov ecx, 1
  rep movsb
  ;inc edi
  jmp   buscarfin
len:
  xor   ecx, ecx ;limpiar
siguiente:
  cmp   [edi], byte ' '  ;fin de cadena
  jz    salir
  inc   ecx
  inc   edi
  jmp   siguiente
salir:
  mov   eax, ecx      ; guardar en eax
  ret                  ; salir
  imprimir:
      mov ecx, espDigito
      mov ebx, 10
      mov [ecx], ebx
      inc ecx
      mov [posDigito], ecx

    bucle:
       mov edx, 0
       mov ebx, 10
       div ebx
       ;push eax
       add edx, 48

       mov ecx, [posDigito]
       mov [ecx], dl
       inc ecx
       mov [posDigito], ecx

       ;pop eax
       cmp eax, 0
       jne bucle

    bucle2:
       mov ecx, [posDigito]
    ;_WriteConsoleA
    ;    mov eax, 1
    ;    mov edi, 1
    ;    mov rsi, ecx
    ;    mov edx, 1

           ;mov dword [caract],
           push dword-11
           xor eax,eax;
           call _GetStdHandle@4;
           mov [handleConsola],eax;
           xor eax,eax;
           mov eax,0d;
           mov [ultimoArgumento],eax;
           push dword [ultimoArgumento];
           push dword caractEscritos;
           push dword 1;
           push dword ecx
           push dword [handleConsola];
           call _WriteConsoleA@20;


       mov ecx, [posDigito]
       dec ecx
       mov [posDigito], ecx

       cmp ecx, espDigito
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
