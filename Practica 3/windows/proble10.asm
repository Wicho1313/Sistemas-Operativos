;nasm -f win32 -o proble10.obj proble10.asm
;ld proble10.obj -m i386pe -e _start -L "C:\Users\luisg\Documents\SistemasOperativos\Practica 3" -l kernel32 -o proble10.exe
segment .data
  l1 dd 1
  l2 dd 1
  l3 dd 1
  l4 dd 1
  salto db 0xa
section .bss
handleConsola resd 1
caractEscritos resd 1
longitudCadena resd 1
ultimoArgumento resd 1
  s1 resb 50
  s2 resb 50
  s3 resb 50
  d resb 150


segment .text
global _start
extern _GetStdHandle@4
extern _ReadConsoleA@20
extern _WriteConsoleA@20
extern _ExitProcess@4

_start: push dword -10
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
        push dword [longitudCadena]
        push dword s1
        push dword [handleConsola]
        call _ReadConsoleA@20

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
        push dword [longitudCadena]
        push dword s2
        push dword [handleConsola]
        call _ReadConsoleA@20

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
        push dword [longitudCadena]
        push dword s3
        push dword [handleConsola]
        call _ReadConsoleA@20

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
push dword-11
        call _GetStdHandle@4;
        mov [handleConsola],eax;
        xor eax,eax;
        mov eax,0d;
        mov [ultimoArgumento],eax;
        push dword [ultimoArgumento];
        push dword caractEscritos;
        push dword [l4];
        push dword d;
        push dword [handleConsola];
        call _WriteConsoleA@20;

push dword-11
        call _GetStdHandle@4;
        mov [handleConsola],eax;
        xor eax,eax;
        mov eax,0d;
        mov [ultimoArgumento],eax;
        push dword [ultimoArgumento];
        push dword caractEscritos;
        push dword [l4];
        push dword d;
        push dword [handleConsola];
        call _WriteConsoleA@20;

  xor eax,eax;
  mov eax,0d;
  mov [ultimoArgumento],eax;
  push dword [ultimoArgumento];
  call _ExitProcess@4;

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
