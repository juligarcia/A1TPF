#include "main.h"

/*Prototipos de funciones a usar con el nuevo TDA lista*/

nodo_t *lista_crear(void){

	nodo_t *nodo;

	if(!(nodo = (nodo_t *)malloc(sizeof(nodo_t))))
		return NULL;

	nodo->next = NULL;
	nodo->dato = NULL;

	return nodo;
}

void lista_destruir(nodo_t **nodo){

	nodo_t *current = *nodo, *next;

	if(current){
		while(current->next){

			next = current->next;
			free(current);
			current = next;

		} 
		free(current);
		*nodo = NULL;
	}
}