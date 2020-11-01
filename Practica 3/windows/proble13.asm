;nasm -f win32 -o proble13.obj proble13.asm
;ld proble13.obj -m i386pe -e _start -L "C:\Users\luisg\Documents\SistemasOperativos\Practica 3" -l kernel32 -o proble13.exe
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
caract resd 1
handleConsola resd 1
caractEscritos resd 1
longitudCadena resd 1
ultimoArgumento resd 1
  opcion resb 3
  num1 resb 50
  num2 resb 50
  espDigito resb 100
  posDigito resb 8

segment .text
global _start
extern _GetStdHandle@4
extern _ReadConsoleA@20
extern _WriteConsoleA@20
extern _ExitProcess@4
_start:
push dword-11
xor eax,eax;
call _GetStdHandle@4;
mov [handleConsola],eax;
xor eax,eax;
mov eax,0d;
mov [ultimoArgumento],eax;
push dword [ultimoArgumento];
push dword caractEscritos;
push dword introl;
push dword intro
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
push dword opcl;
push dword opc
push dword [handleConsola];
call _WriteConsoleA@20;

push dword -10
call _GetStdHandle@4
mov [handleConsola],eax
xor eax,eax
mov eax,2
mov[longitudCadena],eax
xor eax,eax
mov eax,0d
mov [ultimoArgumento],eax
push dword [ultimoArgumento]
push dword caractEscritos
push dword 3
push dword opcion
push dword [handleConsola]
call _ReadConsoleA@20


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
        push dword 50
        push dword num1
        push dword [handleConsola]
        call _ReadConsoleA@20

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
        push dword 50
        push dword num2
        push dword [handleConsola]
        call _ReadConsoleA@20

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

    mov eax, num1
    call atoi
    push eax

    mov eax, num2
    call atoi
    pop edx
    add eax,edx

    call imprimir

    xor eax,eax;
    mov eax,0d;
    mov [ultimoArgumento],eax;
    push dword [ultimoArgumento];
    call _ExitProcess@4;
res:
    mov eax, num1
    call atoi
    push eax

    mov eax, num2
    call atoi
    pop edx
    cmp eax,edx
    jg cambio

    sub edx,eax

    mov eax, edx
    call imprimir

    xor eax,eax;
    mov eax,0d;
    mov [ultimoArgumento],eax;
    push dword [ultimoArgumento];
    call _ExitProcess@4;
cambio:
    push eax
    push edx

    push dword-11
            call _GetStdHandle@4;
            mov [handleConsola],eax;
            xor eax,eax;
            mov eax,0d;
            mov [ultimoArgumento],eax;
            push dword [ultimoArgumento];
            push dword caractEscritos;
            push dword negal;
            push dword nega;
            push dword [handleConsola];
            call _WriteConsoleA@20;

    pop edx
    pop eax

    sub eax,edx
    call imprimir

    xor eax,eax;
    mov eax,0d;
    mov [ultimoArgumento],eax;
    push dword [ultimoArgumento];
    call _ExitProcess@4;
divi:
    mov eax, num1
    call atoi
    push eax

    mov eax, num2
    call atoi
    mov ebx,eax
    pop eax

    div ebx

    ;mov eax, edx
    call imprimir

    xor eax,eax;
    mov eax,0d;
    mov [ultimoArgumento],eax;
    push dword [ultimoArgumento];
    call _ExitProcess@4;
multi:
    mov eax, num1
    call atoi
    push eax

    mov eax, num2
    call atoi
    mov ebx,eax
    pop eax

    mul ebx

    ;mov eax, edx
    call imprimir

    xor eax,eax;
    mov eax,0d;
    mov [ultimoArgumento],eax;
    push dword [ultimoArgumento];
    call _ExitProcess@4;

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
