/*Proteccion contra inclusion multiple*/

/*Argumentos*/

#ifndef ARGUMENTS__H

#define ARGUMENTS__H

/*Para validacion de cantidad de argumentos*/

#define MIN_ARGC_H 2
#define MIN_ARGC 4

/*Mensajes de error*/

#define MSJ_ERROR_ARG "Argumentos ingresados incorrectamente. Por favor, intente nuevamente."

/*Argumentos por linea de comando validos*/

#define ARG_M "-m"
#define ARG_F "-f"
#define ARG_H "-h"
#define ARG_STDIN "-"

/*Opciones validas seguidas del argumento "-f"*/

#define FMT_TXT "txt"
#define FMT_BIN "bin"

typedef struct flags_t{bool help; bool fotxt; bool fobin; bool stdinn;}flags_t;

/*Prototipo de la funcion para procesamiento de argumentos*/

status_t argument_proc(int argc, char *argv[], flags_t *flags, simpletron_t *simpletron, nodo_t **nodo);

#endif
