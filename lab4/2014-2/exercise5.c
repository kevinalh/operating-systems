/*        exercise5.c               */
/* Ejercicio 1 para depurar con GDB */
/* Laboratorio Nro 4  - S.O.        */
/* 2014 - 2                         */

#include <stdio.h>
#include <stdlib.h>
static void shell_sort(int a[], int size)
{  int i, j;
   int h = 1;
   
   do {
      h = h * 3 + 1;
   } while (h <= size);
   do {
      h /= 3;
      for (i = h; i < size; i++) {
         int v = a[i];
         for (j = i; j >= h && a[j - h] > v; j -= h)
              a[j] = a[j - h];
         if (i != j) a[j] = v;
      }
   } while (h != 1);
}

int main(int argc, char *argv[])
{   int *a;
    int i;
    
    a = (int *)malloc((argc - 1) * sizeof(int));
    for (i = 0; i < argc - 1; i++) a[i] = atoi(argv[i + 1]);
    shell_sort(a, argc);
    for (i = 0; i < argc - 1; i++) printf("%d ", a[i]);
    printf("\n");
    free(a);
    return EXIT_SUCCESS;
}
