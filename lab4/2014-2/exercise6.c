/*        exercise6.c               */
/* Ejercicio 1 para depurar con GDB */
/* Laboratorio Nro 4  - S.O.        */
/* 2014 - 2                         */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void prueba(int a, double b, char c, char *s, int d[]){
    void *p = &a;
    char *s2;

    /*acceso al entero*/
    printf("%p %d\n",p, *(int*)p);

    /*acceso al real*/
    p = (int*)p + 1;
    printf("%p %lf\n", p, *(double*)p);
    p = (double*)p+1;

    /*acceso al char*/
    printf("%p %c\n", p, *(char*)p);
    p =(char*)p+1; 
	
    /*acceso a la cadena*/    
    printf("%p %s\n",p, *(char**)p);
}

int main(int argc, char** argv) {
    int a = 10;
    double b = 19.23;
    char c = 'S';
    char *s="LP2";
    int d[]={17,18,15,19,20};

    printf("antes %p\n", s);
    prueba(a, b, c, s, d);


    return (EXIT_SUCCESS);
}

