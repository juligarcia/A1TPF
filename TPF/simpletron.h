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

#define SEPARATOR "?"
#define END_READ -99999

/*Memoria default para los argumentos de linea de comando*/

#define DEFAULT_MEM_SIZE 50

/*Tipo enumerativos y estructuras usadas en el simpletron*/

typedef enum{OP_LEER = LEER, OP_ESCRIBIR = ESCRIBIR, OP_CARGAR = CARGAR, OP_GUARDAR = GUARDAR, OP_PCARGAR = PCARGAR, OP_PGUARDAR = PGUARDAR, OP_SUMAR = SUMAR, OP_RESTAR = RESTAR, OP_DIVIDIR = DIVIDIR,
OP_MULTIPLICAR = MULTIPLICAR, OP_JMP = JMP, OP_JMPNEG = JMPNEG, OP_JMPZERO = JMPZERO, OP_JNZ = JNZ, OP_DJNZ = DJNZ, OP_HALT = HALT}opcode;

typedef  unsigned short int palabra_t;

typedef struct simpletron_t {vector_t *memory; palabra_t acc; size_t pc; size_t mem;}simpletron_t;

/*OP CODE opciones para poder comparar en switch*/
							
#endif