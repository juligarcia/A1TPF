#include "main.h"

/*Prototipos de funciones a usar con el nuevo TDA vector*/

vector_t * vector_crear(size_t s){

	vector_t *v;

	v = (vector_t *)calloc(1, sizeof(*v));

	if(!v)
		return NULL;

	v->datos = (void**)calloc(1, sizeof(void *)*s);

	if(!v->datos){
		free(v);
		return NULL;
	}

	v->size = s;

	return v;
}


void vector_destruir(vector_t **v){

	int i;

	if(v && *v){
		if((*v)->datos){
			for(i = 0; i < (*v)->size; i++){
				free(((*v)->datos)[i]);
			}

			free((*v)->datos);
		}

		free(*v);

		*v = NULL;
	}
}


void vector_limpiar_datos(vector_t *v){

	int i;

	if(v){
		if(v->datos){
			for(i = 0; i < v->size; i++){
				free(v->datos[i]);
			}
		}
	}
}


bool vector_cargar(vector_t *v, void *dato, int *used){

	if(v->size >= *used)
		return false;

	if(!(v->datos[*used] = (short unsigned int *)malloc(sizeof(short unsigned int)))){
		return false;
	}

	v->datos[*used] = dato;

	*used += 1;

	return true;
}


bool vector_proc_txt(char *filename, vector_t *v, int *used, bool (*vector_cargar)(vector_t *v, void *dato, int *used)){

	int i, aux, bin1, bin2, *dato, aux2;
	char buffer[MAX_BUFFER], *buffer2;
	FILE *fp;

	if(!(fp = fopen(filename, "rt")))
		return false;

	/*Se lee el archivo linea por linea, se transforman sus datos en numeros, dejando de lado los comentarios*/

	while(fgets(buffer, MAX_BUFFER, fp)){

		dato = (int *)malloc(sizeof(short unsigned int));

		aux2 = strtol(buffer, &buffer2, 10);

		if(buffer == buffer2){
			free(dato);
			continue;
		}

		if(aux2 < 0){
			aux2 *= -1;
		}

		if(aux2 == 0 || aux2 < 10000){
		}
			
		else{
			bin1 = aux2;
			bin2 = bin1;

			bin1 /= 10000;

			bin2 -= 10000*bin1;

			bin1 = bin1 << SHIFT_1;

			bin1 = bin1 & MASK_1;

			aux = bin1 | bin2;
		}

		if(aux2 > MAX_SIZE_WORD && aux2 > MIN_SIZE_WORD){
			free(dato);
			fclose(fp);
			return false;
		}

		if(*used >= v->size){
			free(dato);
			fclose(fp);
			return false;
		}

		*dato = (short unsigned int)aux2;

		if(vector_cargar(v, dato, used) == false){
			fclose(fp);
			free(dato);
			return false;
		}

		dato = NULL;
	}

	for(i = *used; i < v->size; i++){

		aux = 0;

		dato = (int *)malloc(sizeof(short unsigned int));
		*dato = (short unsigned int)aux;	
		
		if(vector_cargar(v, dato, used) == false){
			fclose(fp);
			return false;
		}
	}

	fclose(fp); 
	return true;
}


bool vector_proc_stdin(vector_t *v, int *used){
	
	int i, aux = 0, bin1, bin2;
	short unsigned int *dato;
	char buffer[MAX_BUFFER],*ptr;
	
	for(i = 0; i < v->size; i++){

		printf("%02d %s ", i, SEPARATOR);
		
		if(!(fgets(buffer, MAX_BUFFER, stdin)))
			break;

		aux = strtol(buffer, &ptr, 10);

		if(aux == END_READ)
			break;

		if(ptr == buffer)
			continue;

		if(aux < MIN_SIZE_WORD)
			aux *= -1;

		if(aux == 0 || aux < 10000){
		}
			
		else{
			bin1 = aux;
			bin2 = bin1;

			bin1 /= 10000;

			bin2 -= 10000*bin1;

			bin1 = bin1 << SHIFT_1;

			bin1 = bin1 & MASK_1;

			aux = bin1 | bin2;
		}

		if(*ptr != '\0' && *ptr != '\n'){
			return false;
		}

		if(aux > MAX_SIZE_WORD)
			return false;	

		dato = (short unsigned int *)malloc(sizeof(short unsigned int));
		*dato = aux;	
		
		if(vector_cargar(v, dato, used) == false)
			return false;
	}

	for(i = *used; i < v->size; i++){

		aux = 0;

		dato = (short unsigned int *)malloc(sizeof(short unsigned int));
		*dato = aux;	
		
		if(vector_cargar(v, dato, used) == false)
			return false;
	}

	return true;
}


bool vector_proc_bin(char *filename, vector_t *v, int *used, bool (*vector_cargar)(vector_t *v, void *dato, int *used)){

	int i, aux, bin1, bin2;
	FILE *fp;
	short unsigned int *dato;

	if(!(fp = fopen(filename, "rb")))
		return false;

	for(i = 0; i < v->size; i++){
		
		if(fread(&aux, sizeof(int), 1, fp) != 1)
			break;
		
		if(aux < MIN_SIZE_WORD)
			aux *= -1;

		if(aux == 0 || aux < 10000){
		}
			
		else{
			bin1 = aux;
			bin2 = bin1;

			bin1 /= 10000;

			bin2 -= 10000*bin1;

			bin1 = bin1 << SHIFT_1;

			bin1 = bin1 & MASK_1;

			aux = bin1 | bin2;
		}

		if(aux > MAX_SIZE_WORD){
			fclose(fp);
			return false;	
		}

		dato = (short unsigned int *)malloc(sizeof(short unsigned int));
		*dato = aux;	
		
		if(vector_cargar(v, dato, used) == false){
			fclose(fp);
			return false;
		}
	}

	for(i = *used; i < v->size; i++){

		aux = 0;

		dato = (short unsigned int *)malloc(sizeof(short unsigned int));
		*dato = aux;	
		
		if(vector_cargar(v, dato, used) == false){
			fclose(fp);
			return false;
		}
	}

	fclose(fp);
	return true;
}

/*Funciones del vector que se usan en el procesamiento del simpletron*/

bool vector_op_leer(vector_t *v, int operand){
	
	/*Se lee por stdin y se guarda en una posicion de memoria*/

	char buffer[MAX_BUFFER];
	char *ptr;

	short int aux;
	
	if(operand > v->size){
		return false;
	}
	if(!(fgets(buffer, MAX_BUFFER, stdin))){
		return false;
	}
	aux = strtol(buffer, &ptr, 10);
	if(*ptr != '\0' && *ptr != '\n')
		return false;
	
	*(short unsigned int *)v->datos[operand] = aux;
	return true;
}


void vector_op_guardar(vector_t *v, int operand, short unsigned int acc){

	/*Guarda el contenido del acumulador en una posicion de memoria*/

	*(short unsigned int *)v->datos[operand] = acc;

}


void vector_op_guardarp(vector_t *v, int operand, short unsigned int acc){

	/*Es homologa a la funcion guardar, pero con puntero como operando*/

	*(short unsigned int *)v->datos[*(short unsigned int *)v->datos[operand]] = acc;

}