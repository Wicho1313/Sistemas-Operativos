;nasm -f win32 -o proble11.obj proble11.asm
;ld proble11.obj -m i386pe -e _start -L "C:\Users\luisg\Documents\SistemasOperativos\Practica 3" -l kernel32 -o proble11.exe
segment .data

section .bss
  caract resd 1
  handleConsola resd 1
  caractEscritos resd 1
  longitudCadena resd 1
  ultimoArgumento resd 1
  s1 resd 100
  espDigito resd 100
  posDigito resd 8


segment .text
global _start
extern _GetStdHandle@4
extern _ReadConsoleA@20
extern _WriteConsoleA@20
extern _ExitProcess@4

_start:
push dword -10
        call _GetStdHandle@4
        mov [handleConsola],eax
        xor eax,eax
        mov eax,100d
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

    mov edi,s1

    call len
    ;mov eax,126
    sub eax,2




    call imprimir
;_ExitProcess
    xor eax,eax;
    mov eax,0d;
    mov [ultimoArgumento],eax;
    push dword [ultimoArgumento];
    call _ExitProcess@4;


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

len:
  xor   ecx, ecx ;limpiar
  ;mov eax, '*'
siguiente:
  cmp   [edi],byte 0   ;fin de cadena
  je    salir
  inc   ecx
  inc   edi
  jmp   siguiente
salir:

  mov   eax, ecx      ; guardar en eax
  ret                  ; salir
