/*        exercise2.c               */
/* Ejercicio 1 para depurar con GDB */
/* Laboratorio Nro 4  - S.O.        */
/* 2014 - 2                         */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
   int *ptr = malloc(4);
   
   free(ptr);
   printf("Ingrese un entero:");
   scanf("%d",*ptr);
   { int a,b;
      printf("Ingrese dos entero:");
      scanf("%d %d",&a, &b);
      printf("%d ",*ptr);
      printf("%d %d",a,b);
   }   
   return EXIT_SUCCESS;
}   
