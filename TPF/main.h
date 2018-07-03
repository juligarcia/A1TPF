/*Proteccion contra inclusion multiple*/

#ifndef MAIN__H 

#define MAIN__H 

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "vector.h"
#include "lista.h"
#include "simpletron.h"
#include "argument_proc.h"
#include "misc.h"

/*Seleccion del lenguaje, ES ESPAÑOL, US INGLES*/

#define LANG__ES
#include "lang.h"

#define NEXT_PROC "------------------------------------------------"

typedef enum {t, b, e}specifier_t;

char proc_file_name(nodo_t *nodo);

#endif