/*Proteccion contra inclusion multiple*/

#ifndef LISTA__H

#define LISTA__H

typedef struct nodo{
	void *dato;
	struct nodo *next;
} nodo_t;

/*Funciones a usar por el TDA lista*/

nodo_t *lista_crear(void);

void lista_destruir(nodo_t *nodo);

#endif