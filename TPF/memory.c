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


bool vector_cargar(vector_t *v, void *dato, int i, void *(*copiar)(void *)){

	if(!v)
		return false;

	if(i >= v->size || i < 0)
		return false;

	if(!(v->datos))
		return false;

	if(!((v->datos)[i] = (*copiar)(dato)))
		return false;

	return true;
}


/*Como hay varias formas para cargar datos a un vector, se implementar la funcion vector_cargar con un puntero a una funcion copiar. 
A continuacion se implementaran las funciones necesarias de copiar, para asi reusar esta funcion de cargar, pero usando 2 funciones de cargar:
Una por si se pasan los datos por stdin o un txt, y otra para extraer de un bin*/


void *vector_copiar(void *buffer){

	unsigned short int *dato = NULL, j;
	char *aux;

	j = (unsigned short int)strtol(buffer, &aux, 10);

	if(j > MAX_SIZE_WORD)
		return NULL;

	if(aux == buffer)
		return NULL;

	dato = &j;

	return dato;

}