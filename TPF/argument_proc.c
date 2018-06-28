#include "main.h"

/*Funcion de procesamiento de argumentos*/
/*A lo que se apunta con esta funcion, es a un procesamiento no posicional de argumentos, en donde el usuario puede ingresar los argumentos mediante linea de comandos
  en el orden deseado, como por ejemplo poner los nombres de archvios de entrada desordenados e intercalados con otros "flags".*/

status_t argument_proc(int argc, char *argv[], flags_t *flags, simpletron_t *simpletron, char ***fpos){

	/*Los argumentos a esta funcion son los conocidos argc, argv, y los adicionales flags para marca el estado de los parametros, la estructura simpletron, principal para el funcionamiento del programa,
	  que aqui nos sirve para estabelcer la cantidad de memoria a usar. En esta nueva implementacion del trabajo, en esta funcion, se intenta mejorar el procesamiento anterior, y dado que se puede contar 
	  con una cantidad maayor de archivos de entrada, se usara el puntero a int "fpos" para guardar las posiciones respectivas de los nombres de archivos en argv para no recorrer de nuevo argv en el main*/

	int i, size = 0, count = 0, aux;
	char *ptr;

	/*Se inicializa fpos en un puntero NULL dado que en el primer caso de realloc funcionara como malloc, tambien se inicializan algunos flags*/

	*fpos = NULL;
	flags->help = false;
	simpletron->mem = DEFAULT_MEM_SIZE;

	/*Se valida la cantidad minima de argumentos, ya que por lo menos se deberia recibir el argumento "-h", pero como maximo no se tiene tope, dado la cantidad de archivos de entrada*/

	if(argc < MIN_ARGC)
		return ST_ERROR_FEW_ARG;

	/*Se recorre argv en busca de los arguentos y se llevan a cabo los cambios necesarios*/

	for(i = 1; i < argc; i++){

		if(!count){

			if(!strcmp(argv[i], ARG_H)){
				flags->help = true;
			}

			else{

				if(!strcmp(argv[i], ARG_F)){

					if(!strcmp(argv[i + 1], FMT_TXT)){
						flags->fotxt = true;
						flags->fobin = false;
						count = 1;
					}

					else{
					
						if(!strcmp(argv[i + 1], FMT_BIN)){
							flags->fotxt = false;
							flags->fobin = true;
							count = 1;
						}

						else{
							/*Caso default*/
							flags->fotxt = true;
							flags->fobin = false;
						}
					}
				}

				else{

					if(!strcmp(argv[i], ARG_M)){

						if(!(aux = strtol(argv[i + 1], &ptr, 10))){

							if(*ptr != '\0'){
							}

							else{
								simpletron->mem = aux;
								count = 1;
							}
						}
					}

					else{

						if(!strcmp(argv[i], ARG_STDIN))
							flags->stdin = true;
						
						else{
							/*Dado que paso todas las comparaciones con datos utiles para los argumentos establecidos, se determina que el dato restante es un nombre de archivo de entrada
							por lo que se opta por guardar su posicion dentor del vector de cadenas "argv" para su futuro uso*/
							
							size++;

							/*Como se menciono mas arriba, se usara realloc para hacer el vector dinamico y no perder memoria al hacerlo mas grande de lo necesario*/
							/*Se crea un array dinamico de *char*/

							*fpos = (char **)realloc(*fpos, size*sizeof(char *));

							/*Luego se guarda el nombre del archivo ingresado*/

							(*fpos)[size - 1] = (char *)malloc(strlen(argv[i]));
						}
					}
				}
			}
		}

		else{
			count = 0;
		}
	}

	return ST_OK;
}