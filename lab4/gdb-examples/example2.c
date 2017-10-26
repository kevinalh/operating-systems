#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	FILE* fp = fopen("argv[1]", "r");
	char* word;
	while(fscanf(fp, "%s", word) > 0) 
		{}
	return 0;
}
