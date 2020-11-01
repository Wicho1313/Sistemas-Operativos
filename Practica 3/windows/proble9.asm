;seccion de variables
;nasm -f win32 -o proble9.obj proble9.asm
;ld proble9.obj -m i386pe -e _start -L "C:\Users\luisg\Documents\SistemasOperativos\Practica 3" -l kernel32 -o proble9.exe
segment .data
  cont db '0'; se reserva un byte de enters
  enters db 0xA
segment .bss
  handleConsola resd 1
  longitudCadena resd 1
  caractEscritos resd 1
  ultimoArgumento resd 1
segment .text
global _start
extern _GetStdHandle@4;
extern _WriteConsoleA@20;
extern _ExitProcess@4;
_start:

  jmp loopi

loopi:
  cmp byte [cont], ':'
  jne incr
  je fin
fin:
    xor eax,eax;
    mov eax,0d;
    mov [ultimoArgumento],eax;
    push dword [ultimoArgumento];
    call _ExitProcess@4;
incr:
  ;imprime incremento
  push dword-11
          call _GetStdHandle@4;
          mov [handleConsola],eax;
          xor eax,eax;
          mov eax,2d;
          mov [longitudCadena],eax;
          xor eax,eax;
          mov eax,0d;
          mov [ultimoArgumento],eax;
          push dword [ultimoArgumento];
          push dword caractEscritos;
          push dword [longitudCadena];
          push dword cont;
          push dword [handleConsola];
          call _WriteConsoleA@20;
  ;imprime enter
  inc byte [cont]
  jmp _start
