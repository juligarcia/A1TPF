#include "main.h"

bool print_txt(char *file){
	FILE *pf;
	char buff[MAX_BUFFER];

	putchar('\n');

	if((pf = fopen(file, "r")) == NULL){
		return false;
	}
	
	while(fgets(buff, sizeof(buff), pf)){
		printf("%s\n", buff);
	}

	fclose(pf);

	return true;
}
