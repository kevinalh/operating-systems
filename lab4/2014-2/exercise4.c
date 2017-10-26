/*        exercise4.c               */
/* Ejercicio 1 para depurar con GDB */
/* Laboratorio Nro 4  - S.O.        */
/* 2014 - 2                         */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    int j,i=0,n=1000;
    char name[32];
    char *A[n];
    FILE* infile = fopen(argv[1],"r");
    
    while (fscanf(infile,"%s", name) > 0)
       strcpy(A[i++],name);
    /*shift all elements to right by 1*/
    for (j=i; j>0; j--) A[i+1] = A[i] ;
    return EXIT_SUCCESS;
}
