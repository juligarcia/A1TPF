/*Proteccion contra inclusion multiple*/

/*Argumentos*/

#ifndef ARGUMENTS__H

#define ARGUMENTS__H

/*Para validacion de cantidad de argumentos*/

#define MIN_ARGC 2

/*Argumentos por linea de comando validos*/

#define ARG_M "-m"
#define ARG_F "-f"
#define ARG_H "-h"
#define ARG_STDIN "-"

/*Opciones validas seguidas del argumento "-f"*/

#define FMT_TXT "txt"
#define FMT_BIN "bin"

typedef struct flags_t{bool help; bool fotxt; bool fobin; bool stdin;}flags_t;

/*Prototipo de la funcion para procesamiento de argumentos*/

status_t argument_proc(int argc, char *argv[], flags_t *flags, simpletron_t *simpletron, int *fpos);

#endif
