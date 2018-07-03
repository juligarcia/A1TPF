#include "main.h"

/*Funcion de procesamiento de argumentos*/
/*A lo que se apunta con esta funcion, es a un procesamiento no posicional de argumentos, en donde el usuario puede ingresar los argumentos mediante linea de comandos
  en el orden deseado, como por ejemplo poner los nombres de archvios de entrada desordenados e intercalados con otros "flags".*/

status_t argument_proc(int argc, char *argv[], flags_t *flags, simpletron_t *simpletron, nodo_t *nodo){

	/*Los argumentos a esta funcion son los conocidos argc, argv, y los adicionales flags para marca el estado de los parametros, la estructura simpletron, principal para el funcionamiento del programa,
	  que aqui nos sirve para estabelcer la cantidad de memoria a usar. En esta nueva implementacion del trabajo, en esta funcion, se intenta mejorar el procesamiento anterior, y dado que se puede contar 
	  con una cantidad mayor de archivos de entrada, se apuntara con el puntero char *fpos a la posicion de argv donde comienzan los archivos de entrada*/

	int i, count = 0, aux;
	char *ptr;
	nodo_t *temp = NULL;

	/*Se valida la cantidad minima de argumentos, ya que por lo menos se deberia recibir el argumento "-h", pero como maximo no se tiene tope, dado la cantidad de archivos de entrada*/

	if(argc < MIN_ARGC)
		return ST_ERROR_FEW_ARG;

	flags->fotxt = true;
	flags->fobin = false;
	flags->help = false;
	flags->stdinn = false;
	simpletron->mem = DEFAULT_MEM_SIZE;

	/*Se recorre argv en busca de los arguentos y se llevan a cabo los cambios necesarios*/

	for(i = 1; i < argc; i++){

		if(!count){

			if(!strcmp(argv[i], ARG_H)){
				flags->help = true;
				break;
			}

			else{

				if(!strcmp(argv[i], ARG_F)){

					if(!strcmp(argv[i + 1], FMT_TXT)){
						flags->fotxt = true;
						flags->fobin = false;
						count = 1;
					}

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

				else{

					if(!strcmp(argv[i], ARG_M)){

						if((aux = strtol(argv[i + 1], &ptr, 10))){

							if(ptr == argv[i]){
								continue;
							}

							if(*ptr != '\0' && *ptr != '\n'){
								continue;
							}

							simpletron->mem = aux;
							count = 1;					
						}
					}

					else{

						if(!strcmp(argv[i], ARG_STDIN))

							flags->stdinn = true;
						
						else{

							/*Dado que paso todas las comparaciones con datos utiles para los argumentos establecidos, se determina que el/los datos restantes son nombres de archivos de entrada
							por lo que se opta por guardar su posicion, es decir el estado del iterador, en un puntero a int para asi despues poder iterar sobre argv facilemtene */

							
							if(!nodo){
								if(!(nodo = lista_crear()))
									return ST_ERROR_LISTA;
							}

							nodo->dato = (char *)strdup_own(argv[i]);

							temp = nodo;

							i++;

							for(; i < argc; i++){
  								if(!(nodo->next = lista_crear()))
   									return ST_ERROR_LISTA;

  							nodo->next->dato = (char *)strdup_own(argv[i]);

  							nodo = nodo->next;

							}

							nodo = temp;

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