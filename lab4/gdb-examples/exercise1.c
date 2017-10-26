#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100000
#define MAXS 1000

int main() {
	char* a[MAXN];
	int i = 0;
	char* word = (char*) malloc(MAXS*sizeof(char));
	while(i < MAXN && fscanf(stdin, "%s", word) > 0) {
		a[i] = (char*) malloc(strlen(word)*sizeof(char));
		strcpy(a[i], word);
		i++;
	}
	return 0;
}
