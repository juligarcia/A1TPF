/*Proteccion contra inclusion multiple*/

#ifndef SIMPLETRON__H

#define SIMPLETRON__H

/*Defines de codig Op code*/

#define LEER 10
#define ESCRIBIR 11
#define CARGAR 20
#define GUARDAR 21
#define PCARGAR 22
#define PGUARDAR 23
#define SUMAR 30
#define RESTAR 31
#define DIVIDIR 32
#define MULTIPLICAR 33
#define JMP 40
#define JMPNEG 41
#define JMPZERO 42
#define JNZ 43
#define DJNZ 44
#define HALT 45
#define END_READ -99999

/*Memoria default para los argumentos de linea de comando*/

#define DEFAULT_MEM_SIZE 50

/*Tipo enumerativos y estructuras usadas en el simpletron*/

typedef enum{ARG_LEER = LEER, ARG_ESCRIBIR = ESCRIBIR, ARG_CARGAR = CARGAR, ARG_GUARDAR = GUARDAR, ARG_PCARGAR = PCARGAR, ARG_PGUARDAR = PGUARDAR, ARG_SUMAR = SUMAR, ARG_RESTAR = RESTAR, ARG_DIVIDIR = DIVIDIR,
ARG_MULTIPLICAR = MULTIPLICAR, ARG_JMP = JMP, ARG_JMPNEG = JMPNEG, ARG_JMPZERO = JMPZERO, ARG_JNZ = JNZ, ARG_DJNZ = DJNZ, ARG_HALT = HALT}opcode;

typedef int palabra_t;

typedef struct simpletron_t {palabra_t *palabras; palabra_t acc; size_t pc; int mem;}simpletron_t;

/*OP CODE opciones para poder comparar en switch*/
							
#endif