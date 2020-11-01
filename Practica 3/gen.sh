
#verifica que solo sea un elemento
if [ $# -eq 1 ]
then
  echo "Compilando y Enlazando ..."

  nasm -f elf64 $1.asm; ld $1.o -o $1
  if [ $? -eq 0 ]
  then
    echo "Ejectutando ..."
    ./$1
  else
    echo "Error al compilar y enlazar" >&2
  fi

else
  #mensaje de error
  echo "Error"
  echo "Solo debe haber 1 argumento"
  echo "El argumento debe ser el archivo a compilar sin la extension .asm"
fi
