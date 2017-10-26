/*        exercise3.c               */
/* Ejercicio 1 para depurar con GDB */
/* Laboratorio Nro 4  - S.O.        */
/* 2014 - 2                         */

#include <stdlib.h>

void foo(int ***, int);

int main(int argc, char* argv[]){
   int **A;
   int n=2;
   foo(&A,n);
   return 0;
}

void foo(int ***array, int n){
   int **arrayint = (int**)malloc(2*n*sizeof(int*));
   int i;
   
   for (i=0;i<n;i++) arrayint[i] = (*array)[i];
   free(*array);
   array = &arrayint;
}
