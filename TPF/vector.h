/*Proteccion contra inclusion multiple*/

#ifndef VECTOR__H

#define VECTOR__H

/*Se define la interfaz del TDA vector que se usará como memoria*/

#define MAX_SIZE_WORD 65535
#define MIN_SIZE_WORD -32768

#define SHIFT_1 9
#define MASK_1 0xfe00
#define MASK_2 0x7f

typedef struct vector{
	size_t size;
	void **datos;
} vector_t;

void vector_cargar(vector_t *v, void *dato, int *used);

vector_t * vector_crear(size_t s);

void vector_proc(vector_t *v);

void vector_destruir(vector_t *v);

#endif