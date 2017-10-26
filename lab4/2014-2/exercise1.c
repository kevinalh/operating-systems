/*        exercise1.c               */
/* Ejercicio 1 para depurar con GDB */
/* Laboratorio Nro 4  - S.O.        */
/* 2014 - 2                         */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
  char *name = malloc(strlen(argv[1]));
  
  name = strcpy(name,argv[1]);
  printf("%s \n", name);
  return EXIT_SUCCESS;
}      
