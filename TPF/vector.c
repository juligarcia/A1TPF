#include "main.h"

/*Prototipos de funciones a usar con el nuevo tipo de dato abstracto*/

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


void vector_destruir(vector_t *v){

	if(v){
		if(v->datos)
			free(v->datos);
		free(v);
		v = NULL;
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


void vector_proc (vector_t *v){

	/*Hay que analizar los limites de estos parametros. Como la palabra sin procesar se guarda en una memoria con capacidad de 16bits el mayor numero posible a guardar es 65535. Esto se valida en la 
	etapa anterior, por lo que los numeros ingresados seran menores a este. El mayor opcode posible sera 065*/

	palabra_t *aux, *aux2;
	int i;

	for(i = 0; i < v->size; i++){

		aux = (palabra_t *)v->datos[i];
		aux2 = (palabra_t *)v->datos[i];

		*aux /= 10000;

		*aux2 -= 10000*(*aux);

		(*aux) << SHIFT_1;
		(*aux) = (*aux) & MASK_1;

		(*(palabra_t *)v->datos[i]) = (*aux) | (*aux2);
		
	}
}

