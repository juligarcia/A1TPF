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
				free((*v)->datos[i]);
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

	if(!(v->datos[*used] = (palabra_t *)malloc(sizeof(palabra_t)))){
		free(v->datos[*used]);
		return false;
	}

	v->datos[*used] = dato;

	*used += 1;

	return true;
}


void vector_proc (vector_t **v){

	/*Hay que analizar los limites de estos parametros. Como la palabra sin procesar se guarda en una memoria con capacidad de 16bits y estas son con signo
	el mayor numero posible a guardar es 32768 y -32768. Esto se valida en la etapa anterior, por lo que los numeros ingresados seran menores a este. El mayor opcode posible sera 032*/

	palabra_t *aux, *aux2;
	int i;

	for(i = 0; i < (*v)->size; i++){

		aux = (palabra_t *)(*v)->datos[i];
		aux2 = (palabra_t *)(*v)->datos[i];

		*aux /= 10000;
puts("3");
		*aux2 -= 10000*(*aux);
puts("4");
		(*aux) << SHIFT_1;
		(*aux) = (*aux) & MASK_1;
puts("5");
		(*(palabra_t *)(*v)->datos[i]) = (*aux) | (*aux2);
		
	}
}

