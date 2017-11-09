#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct {
	int a;
	double b;
	char c;
	char* s;
	int d[5];
} struct_t;

void prueba(struct_t k){
    void *p = &(k.a);
    char *s2;

    /*acceso al entero*/
    printf("%p %d\n",p, *(int*)p);

    /*acceso al real*/
    p = (double*)p + 1;
    printf("%p %lf\n", p, *(double*)p);
    p = (char*)p + 1;

    /*acceso al char*/
    printf("%p %c\n", p, *(char*)p);
    p =(char**)p + 1; 
	
    /*acceso a la cadena*/    
    printf("%p %s\n",p, *(char**)p);
}

int main(int argc, char** argv) {
    struct_t k;
		k.a = 10;
   	k.b = 19.23;
    k.c = 'S';
    k.s = "LP2";
    k.d[0] = 17;
		k.d[1] = 18;
		k.d[2] = 15;
		k.d[3] = 19;
		k.d[4] = 20;
    printf("antes %p\n", k.s);
    prueba(k);

    return (EXIT_SUCCESS);
}

