/*Proteccion contra inclusion multiple*/

#ifndef MEMORy__H

#define MEMORy__H

/*Se define la interfaz del TDA vector que se usará como memoria*/

typedef struct vector{
	size_t size;
	void **datos;
} vector_t;

bool vector_cargar(vector_t *v, void *dato, int i, void *(*copiar)(void *));

vector_t * vector_crear(size_t s);

void *vector_copiar(void *buffer);

void vector_destruir(vector_t *v);

#endif