#include "main.h"

int main(int argc, char *argv[]){

	flags_t flags;
	simpletron_t simpletron;
	int j = 1, used = 0;
	nodo_t *nodo = (nodo_t *)malloc(sizeof(nodo_t)), *nodo_aux = NULL;
	FILE *output;

	/*Se inicializan el program counter (pc) y el acumulador (acc) en 0*/

	simpletron.acc = 0;
	simpletron.pc = 0;

	/*Se inicia el procesamiento de argumentos*/

	if(argument_proc(argc, argv, &flags, &simpletron, nodo) != ST_OK)
		return EXIT_FAILURE;

	/*Si el estado del flag "-h" se encuentra en true, se imprime la ayuda en pantalla y luego se termina la operacion del programa*/

	if(flags.help == true){
		print_txt(FILE_HELP);
		lista_destruir(&nodo);
		free(nodo);
		return EXIT_SUCCESS;
	}
	
	/*Se debe crear la estructura para la memoria del Simpletron*/

	if(!(simpletron.memory = vector_crear(simpletron.mem)))
		return EXIT_FAILURE;
	
	/*Se imprimen los mensajes de bienvenida*/

	print_txt(FILE_WELCOME);

	/*Se abre el archivo correspondiente para el dump final. Se abre antes, dado que despues entra en un ciclo, es mas comodo dejarlo abierto e ir agregando datos*/

	if(flags.fotxt == true && flags.fobin  == false){
		if(!(output = fopen(DUMP_TXT, "w")))
			return EXIT_FAILURE;
	}

	if(flags.fotxt == false && flags.fobin  == true){
		if(!(output = fopen(DUMP_BIN, "wb")))
			return EXIT_FAILURE;
	}

	/*Se verfica el STREAM de entrada de datos*/

	if(flags.stdinn == true){

		if(vector_proc_stdin(simpletron.memory, &used) == false)
			return EXIT_FAILURE;

		/*Se inicia el procesamiento del simpletron*/

		if(proc_simpletron(&simpletron) == false)
			return EXIT_FAILURE;

		printf("%s\n\n", MSJ_FIN_DEL_PROGRAMA);	

		/*Una vez procesados los datos, se hace el dump correspondiente*/

		if(flags.fotxt == true && flags.fobin  == false)
			dump_txt(simpletron, output, MSJ_STDOUT);

	}

	else{

		/*Si no entra en el if, quiere decir que el flag es false, por lo que no debera ser por stdin la entrada de datos, hay que verificar si hay archivos de entrda.
	  	De ser asi, deberia haber un nodo creado en la lista, con al menos un archivo guardado*/

		if(!(nodo->dato))
			return EXIT_FAILURE;

		/*Se imprimen los nombres de archivos de entrada y se procesan a la vez*/

		nodo_aux = nodo;

		while(nodo_aux){
			simpletron.acc = 0;
			used = 0;

			printf("%s\n\n", NEXT_PROC);
			
			switch(proc_file_name(nodo_aux)){

				case SPECIFIER_TXT:				
					vector_proc_txt((char *)nodo_aux->dato, simpletron.memory, &used, vector_cargar);
					printf("%s[%d]: %s\n\n", MSJ_ENTRY_FILE, j, (char *)nodo_aux->dato);
					break;

				case SPECIFIER_BIN:				
					vector_proc_bin((char *)nodo_aux->dato, simpletron.memory, &used, vector_cargar);
					printf("%s[%d]: %s\n\n", MSJ_ENTRY_FILE, j, (char *)nodo_aux->dato);
					break;

				default:
					continue;
			}
			
			simpletron.memory->used = used;
			simpletron.memory->size = simpletron.mem;

			/*Se inicia el procesamiento del simpletron*/

			if(proc_simpletron(&simpletron) == false)
				return EXIT_FAILURE;

			printf("%s\n\n", MSJ_FIN_DEL_PROGRAMA);	

			/*Una vez procesados los datos, se hace el dump correspondiente*/

			if(flags.fotxt == true && flags.fobin  == false)
				dump_txt(simpletron, output, (char *)nodo_aux->dato);

			vector_limpiar_datos(simpletron.memory);

			if(nodo_aux->next){
				nodo_aux = nodo_aux->next;
			}
			else{
				break;
			}
		}
	}

fclose(output);

lista_destruir(&nodo);
vector_destruir(&(simpletron.memory));

return EXIT_SUCCESS;

}

