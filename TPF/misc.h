/*Proteccion contra inclusion multiple*/

#ifndef PRINT__H 

#define PRINT__H 

#define MSJ_STDOUT "Standard Out"

/*Macros para la funcion de procesar el nombre de los archivos*/

#define FILE_SPECIFIER ':'
#define SPECIFIER_LEN 1
#define SPECIFIER_TXT 't'
#define SPECIFIER_BIN 'b'
#define SPECIFIER_ERROR 'e'

/*Tamaño standar de buffer*/

#define MAX_BUFFER 100

/*Nombre del archivo de salida para el dump en txt y binario*/

#define DUMP_TXT "dump.txt"
#define DUMP_BIN "dump.bin"

char proc_file_name(nodo_t *nodo);

bool print_txt(char *file);

void dump_txt(simpletron_t simpletron, FILE *pf, char *filename);

#endif