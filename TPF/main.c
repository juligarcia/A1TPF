#include "main.h"

int main(int argc, char *argv[]){

	flags_t flags;
	simpletron_t simpletron;
	int i, j = 1, fpos = 0, used = 0;

	/*Se inicializan el program counter (pc) y el acumulador (acc) en 0*/

	simpletron.acc = 0;
	simpletron.pc = 0;

	/*Se inicia el procesamiento de argumentos*/

	if(argument_proc(argc, argv, &flags, &simpletron, &fpos) != ST_OK)
		return EXIT_FAILURE;

	/*Si el estado del flag "-h" se encuentra en true, se imprime la ayuda en pantalla y luego se termina la operacion del programa*/

	if(flags.help == true){
		print_txt(FILE_HELP);
		return EXIT_SUCCESS;
	}

	/*Se debe crear la estructura para la memoria del Simpletron*/

	if(!(simpletron.memory = vector_crear(simpletron.mem)))
		return EXIT_FAILURE;

	/*Se imprimen los mensajes de bienvenida*/

	print_txt(FILE_WELCOME);

	/*Se verfica el STREAM de entrada de datos*/

	if(flags.stdin == true){

		if(proc_stdin(simpletron.memory, &used) == false)
			return EXIT_FAILURE;

	}

	else{

		/*Si no entra en el if, quiere decir que el flag es false, por lo que no debera ser por stdin la entrada de datos, hay que verificar si hay archivos de entrda.
	  	De ser asi, el valor de fpos deberia ser diferente de 0, ya que 0 es un valor incorrecto. 
	  	En caso de que no pase la validacion se terminara el programa*/

		if(!fpos)
			return EXIT_FAILURE;

		/*Como se pueden ingresar varios archivos de entrada al programa, en la funcion argument_proc se guarda la direccion del primer nombre de archivo*/
		/*Se imprimen los nombres de archivos de entrada y se procesan a la vez*/

		for(i = fpos; i < argc; i++, j++){

			printf("%s[%d]: %s", MSG_ENTRY_FILE, j, argv[i]);

			switch(proc_file_name(&argv[i])){

				case t:
					proc_txt(argv[i], simpletron.memory, &used, vector_cargar);
					break;

				case b:
					proc_bin(argv[i], simpletron.memory, &used);
					break;

				case e:
					return EXIT_FAILURE;
			}
		}
	}

/*Se procesan los datos guardados en la memoria. Dado que cada dato ingresado es una palabra da 7 digitos con signo, estas se deben procesar de forma tal que los 7 bits de mayor significancia
 seran el opcode, y los 9 de menor significancia seran el operando*/

vector_proc(simpletron.memory);

/*Se inicia el procesamiento del simpletron*/

if(proc_simpletron(&simpletron) == false)
	return EXIT_FAILURE;


return 0;




}


char proc_file_name(char **fname){

	char *aux;

	/*Se busca el caracter ':' dentro del string de nombre del archivo*/
	/*Si no se encuentra se interpreta como txt*/

	if(!(aux = strchr(*fname, FILE_SPECIFIER)))
		return SPECIFIER_TXT;

	/*En caso de ser encontrado, se interpreta lo que se encuentra antes de este caracter, de ser un string de mas de largo mas de 1, se considera parte del nombre del archivo y se interpreta como txt.
	En caso de tener largo 1 lo que se encuentre antes, se comparara con los especificadores de binario y texto, 'b' y 't', respectivamente, para determinar que tipo de archivo es. En caso de no ser ninguno de estos
	tambien se considerara parte del nombre del archivo y se dira que es un .txt*/

	if((strlen(*fname) - strlen(aux)) != SPECIFIER_LEN)
		return SPECIFIER_TXT;

	/*En caso de que el formato sea "b:namefile" o "t:namefile" se corre el puntero hacia el primer caracter donde empieza el nombre*/

	if(*fname[0] == SPECIFIER_BIN){
		*fname += 2;
		return SPECIFIER_BIN;
	}

	if(*fname[0] == SPECIFIER_TXT){
		*fname += 2;
		return SPECIFIER_TXT;
	}

	return SPECIFIER_ERROR;

} 


bool proc_txt(char *filename, vector_t *v, int *used, bool (*vector_cargar)(vector_t *v, void *dato, int *used)){

	char buffer[MAX_BUFFER], *buffer2;
	FILE *fp;
	palabra_t *dato;

	if(!(fp = fopen(filename, "r")))
		return false;

	/*Se lee el archivo linea por linea, se transforman sus datos en numeros, dejando de lado los comentarios*/

	while(fgets(buffer, MAX_BUFFER, fp)){

		dato = (palabra_t *)malloc(sizeof(palabra_t));

		*dato = (palabra_t)strtol(buffer, &buffer2, 10);

		if(buffer == buffer2){
			free(dato);
			continue;
		}

		if(*dato > MAX_SIZE_WORD && *dato > MIN_SIZE_WORD){
			free(dato);
			return false;
		}

		if(*used >= v->size){
			free(dato);
			return false;
		}

		if(vector_cargar(v, dato, used) == false)
			return false;

		dato = NULL;
	}

	fclose(fp);

	return true;
}

bool proc_bin(char *filename, vector_t *v, int *used){

return true;
}



bool proc_stdin(vector_t *v, int *used){
	
	int i, aux = 0;
	char buffer[MAX_BUFFER],*ptr;
	
	for(i = 0; i < v->size; i++){

		printf("%02d %s ", i, SEPARATOR);
		
		if(!(fgets(buffer, MAX_BUFFER, stdin)))
			break;

		aux = strtol(buffer, &ptr, 10);

		if(aux == END_READ)
			break;

		if(ptr == buffer)
			return false;

		if(*ptr != '\0' && *ptr != '\n')
			return false;
		
		if(aux < MIN_SIZE_WORD || aux > MAX_SIZE_WORD)
				return false;

		if(vector_cargar(v, &aux, used) == false)
			return false;

		*used += 1;

	}

	return true;
}

bool proc_simpletron(simpletron_t *simpletron){

	int i = 0, k, op_code, operand;
	
	printf("%s\n\n", MSJ_COMIENZO_PROC);

	for(k = 0; k < simpletron->memory->size && i == 0; k++){

		op_code = *(palabra_t *)simpletron->memory->datos[k];
		op_code = op_code >> SHIFT_1;
		op_code = op_code & MASK_2;

		operand = (*(palabra_t *)simpletron->memory->datos[k]) & ~MASK_1;

		switch (op_code){
			
			case OP_LEER: 
				printf("%s [%02d]\n", MSJ_INGRESE_POS, operand);

				if(vector_op_leer(simpletron->memory, operand) != true)
					return false;

				simpletron->pc = k;

				printf("\n");

				break;

			case OP_ESCRIBIR: 		
				printf("%s [%02d]: %d\n", MSJ_POS, operand, *(palabra_t *)simpletron->memory->datos[operand]);
				simpletron->pc = k;

				break;								
			
			case OP_CARGAR: 		
				simpletron_op_cargar(simpletron, operand);	
				simpletron->pc = k;

				break;
			
			case OP_GUARDAR:
				vector_op_guardar(simpletron->memory, operand, simpletron->acc);
				simpletron->pc = k;

				break;

			case OP_PCARGAR: 
				simpletron_op_cargarp(simpletron, operand);
				simpletron->pc = k;

				break;

			case OP_PGUARDAR: 
				vector_op_guardarp(simpletron->memory, operand, simpletron->acc);
				simpletron->pc = k;

				break;

			case OP_SUMAR: 
				simpletron_op_sumar(simpletron, operand);
				simpletron->pc = k;

				break;

			case OP_RESTAR:
				simpletron_op_restar(simpletron, operand);
				simpletron->pc = k;

				break;

			case OP_DIVIDIR: 	
				simpletron_op_dividir(simpletron, operand);
				simpletron->pc = k;

				break;

			case OP_MULTIPLICAR: 	
				simpletron_op_multiplicar(simpletron, operand);
				simpletron->pc = k;

				break;

			case OP_JMP: 
				if(simpletron_op_jmp(simpletron->memory, &k, operand) == false)
					return false;

				break;

			case OP_JMPNEG: 
				if(simpletron_op_jmpneg(simpletron, &k, operand) == false)
					return false;

				simpletron->pc = k;
				
				break;

			case OP_JMPZERO: 
				if(simpletron_op_jmpzero(simpletron, &k, operand) == false)
					return false;

				simpletron->pc = k;

				break;

			case OP_JNZ: 
				if(simpletron_op_jmz(simpletron, &k, operand) == false)
					return false;

				break;

			case OP_DJNZ: 		
				simpletron_op_djnz(simpletron, &k, operand);

				simpletron->pc = k;

				break;	

			case OP_HALT: 

				i = 1;

				simpletron->pc = k;

				printf("%s\n\n", MSJ_FIN_DEL_PROGRAMA);		
				
				break;		
										
			default: 

				/*El caso default, es que es un dato por lo que se debe proceder a la proxima instruccion*/

				break;
			}		
		}

	return true;

}



bool vector_op_leer(vector_t *v, int operand){
	
	/*Se lee por stdin y se guarda en una posicion de memoria*/

	char buffer[MAX_BUFFER];
	char *ptr;

	short int aux;

	if(operand > v->size)
		return false;
		
	if(!(fgets(buffer, MAX_BUFFER, stdin)))
		return false;

	aux = strtol(buffer, &ptr, 10);
	
	if(*ptr != '\0' && *ptr != '\n')
		return false;

	*(palabra_t *)v->datos[operand] = aux;

	return true;
}


void simpletron_op_cargar(simpletron_t *simpletron, int operand){
	
	/*Carga una palabra de la memoria al acumulador*/

	simpletron->acc = *(palabra_t *)simpletron->memory->datos[operand];

}


void vector_op_guardar(vector_t *v, int operand, palabra_t acc){

	/*Guarda el contenido del acumulador en una posicion de memoria*/

	*(palabra_t *)v->datos[operand] = acc;

}


void simpletron_op_sumar(simpletron_t *simpletron, int operand){

	/*Suma una palabra al acumulador*/

	simpletron->acc += *(palabra_t *)simpletron->memory->datos[operand];

}


void simpletron_op_restar(simpletron_t *simpletron, int operand){

	/*Resta una palabra al acumulador*/

	simpletron->acc -= *(palabra_t *)simpletron->memory->datos[operand];

}


void simpletron_op_dividir(simpletron_t *simpletron, int operand){

	/*Divide al acumulador por el contenido de la posicion de memoria indicada por el interador "i"*/

	simpletron->acc /= *(palabra_t *)simpletron->memory->datos[operand];	

}


void simpletron_op_multiplicar(simpletron_t *simpletron, int operand){

	/*Multiplicar al acumulador por el contenido de la posicion de memoria indicada por el interador "i"*/

	simpletron->acc *= *(palabra_t *)simpletron->memory->datos[operand];
	
}


bool simpletron_op_jmp(vector_t *v, int *k, int operand){

	/*Salta a la orden especificada*/

	if(operand > v->size)
		return false;

	*k = operand - 1 ;

	return true;

}	


bool simpletron_op_jmpneg(simpletron_t *simpletron, int *k, int operand){

	/*Salta a la orden especificada SOLO SI el acumulador es negativo*/

	if(operand > simpletron->memory->size)
			return false;

	if(simpletron->acc < 0){
		*k = operand - 1 ;
		return true;
	}

	else
		return false;
}


bool simpletron_op_jmpzero(simpletron_t *simpletron, int *k, int operand){

	/*Salta a la orden especificada SOLO SI el acumulador es 0*/

	if(operand > simpletron->memory->size)
		return false;
	
	if(simpletron->acc == 0){
		*k= operand - 1 ;
		return true;
	}

	else
		return false;
}


bool simpletron_op_jmz(simpletron_t *simpletron, int *k, int operand){

	/*Salta a la orden especificada SOLO SI el acumulador es distinto de 0*/

	if(operand > simpletron->memory->size)
		return false;

	if((simpletron->acc)){
		*k = operand - 1;
		return true;
	}

	else
		return false;
}


void simpletron_op_djnz(simpletron_t *simpletron, int *k, int operand){

	/*Decrementa el acumulador por el contenido de la posicion de memoria indicado y, si este no es 0, vuelve al comienzo del ciclo*/

	if((simpletron->acc -= *(palabra_t *)simpletron->memory->datos[operand]) == 0) 
		*k = -1;

}


void simpletron_op_cargarp(simpletron_t *simpletron, int operand){

	/*Es homologa a la funcion cargar, pero se indica una posicion de memoria donde se sacara un puntero*/

	simpletron->acc = *(palabra_t *)simpletron->memory->datos[*(palabra_t *)simpletron->memory->datos[operand]]; 

}


void vector_op_guardarp(vector_t *v, int operand, palabra_t acc){

	/*Es homologa a la funcion guardar, pero con puntero como operando*/

	*(palabra_t *)v->datos[*(palabra_t *)v->datos[operand]] = acc;

}