/*Proteccion contra inclusion multiple*/

#ifndef MAIN__H 

#define MAIN__H 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "vector.h"
#include "simpletron.h"
#include "argument_proc.h"

/*Seleccion del lenguaje, ES ESPAÑOL, US INGLES*/

#define LANG__ES
#include "lang.h"

#define FILE_SPECIFIER ':'
#define SPECIFIER_LEN 1
#define SPECIFIER_TXT 't'
#define SPECIFIER_BIN 'b'
#define SPECIFIER_ERROR 'e'

typedef enum {t, b, e}specifier_t;

char proc_file_name(char **fname);

bool proc_txt(char *filename, vector_t *v, int *used, void (*vector_cargar)(vector_t *v, void *dato, int *used));

bool proc_bin(char *filename, vector_t *v, int *used);

bool proc_stdin(vector_t *v, int *used);

#define MAX_BUFFER 100


#endif