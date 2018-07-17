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

char proc_file_name(nodo_t *nodo){

	char *aux;

	/*Se busca el caracter ':' dentro del string de nombre del archivo*/
	/*Si no se encuentra se interpreta como txt*/

	if(!(aux = strchr(nodo->dato, FILE_SPECIFIER)))
		return SPECIFIER_TXT;

	/*En caso de ser encontrado, se interpreta lo que se encuentra antes de este caracter, de ser un string de mas de largo mas de 1, se considera parte del nombre del archivo y se interpreta como txt.
	En caso de tener largo 1 lo que se encuentre antes, se comparara con los especificadores de binario y texto, 'b' y 't', respectivamente, para determinar que tipo de archivo es. En caso de no ser ninguno de estos
	tambien se considerara parte del nombre del archivo y se dira que es un .txt*/

	if((strlen(nodo->dato) - strlen(aux)) != SPECIFIER_LEN)
		return SPECIFIER_TXT;

	/*En caso de que el formato sea "b:namefile" o "t:namefile" se corre el puntero hacia el primer caracter donde empieza el nombre*/

	if(((char*)nodo->dato)[0] == SPECIFIER_BIN){
		nodo->dato = (char *)nodo->dato + 2;
		return SPECIFIER_BIN;
	}

	if(((char *)nodo->dato)[0] == SPECIFIER_TXT){		
		nodo->dato = ((char *)(nodo->dato)+ 2);		
		return SPECIFIER_TXT;
	}

	return SPECIFIER_ERROR;

} 

void dump_txt(simpletron_t simpletron, FILE *pf, char *filename){

	int op_code, operand, fil, i, j;

	fprintf(pf, "\n");

	fprintf(pf, "%s", NEXT_PROC);

	fprintf(pf, "\n");

	fprintf(pf, "%s:[%s]\n", MSJ_DUMP_FILE, filename);
	
	fprintf(pf, "%s\n", MSJ_REGISTRO);

	fprintf(pf, "%15s:%5x\n", MSJ_ACUMULADOR, simpletron.acc);

	fprintf(pf, "%15s:%5ld\n", MSJ_PCOUNT, simpletron.pc);

	fprintf(pf, "%15s:%+5d\n", MSJ_INSTRUCCION, *(palabra_t *)simpletron.memory->datos[simpletron.pc]);

	op_code = *(palabra_t *)simpletron.memory->datos[simpletron.pc];
	op_code = op_code >> SHIFT_1;
	op_code = op_code & MASK_2;

	operand = (*(palabra_t *)simpletron.memory->datos[simpletron.pc]) & ~MASK_1;

	fprintf(pf, "%15s:%5.02d\n", MSJ_OPCODE, op_code);

	fprintf(pf, "%15s:%5.02d\n\n", MSJ_OPERANDO, operand);

	/*Se imprime la memoria en forma de matriz*/
    /*Se calcula la cantidad de filas correspondientes dependiendo de la cantidad de memoria que se pidio ingresando el argumento "-m"*/

    if(((simpletron.memory->size) % 16) != 0)
        fil = (simpletron.memory->size / 16) + 1;
    
    else
        fil = (simpletron.memory->size) / 16;

    for(i = 0; i < fil; i++){

    	if(i)
    		fprintf(pf, "\n");

    	fprintf(pf, "%03x", 16*i);

    	for(j = 0; j < 16; j++){

    		if(j + (i*16) < simpletron.mem)
    			fprintf(pf, "%7.04x", *(palabra_t *)simpletron.memory->datos[j + (i*16)]);
    		
    		else
    			continue;

    	}
    }
   
    fprintf(pf, "\n");
}


bool dump_bin(simpletron_t simpletron, FILE *pf, char *filename){

	int i;	
	
	for(i = 0; i < simpletron.mem; i++){
		
		if(fwrite((palabra_t *)simpletron.memory->datos[i], 1, sizeof(palabra_t), pf) != 1){
			return false;
		}		
	}

	return true;
}


/*Implementacion de la funcion strdup pero propia, ya que esta traia problemas al compilar en distintas maquinas*/

char *strdup_own(const char *str){

	int n = strlen(str) + 1;

	char *dup = malloc(n);

	if(dup)
		strcpy(dup, str);

	return dup;
}