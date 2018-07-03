#include "main.h"

bool proc_simpletron(simpletron_t *simpletron){

	int i = 0, k, op_code, operand;
	
	printf("%s\n\n", MSJ_COMIENZO_PROC);

	for(k = 0; (k < simpletron->mem) && (i == 0); k++){

		op_code = *(palabra_t *)simpletron->memory->datos[k];
		op_code = op_code >> SHIFT_1;
		op_code = op_code & MASK_2;
		operand = (*(palabra_t *)simpletron->memory->datos[k]) & ~MASK_1;

		switch (op_code){
			
			case OP_LEER: 
				printf("%s [%02d]\n", MSJ_INGRESE_POS, operand);

				if(vector_op_leer(simpletron->memory, operand) != true)
					return false;

				simpletron->pc = k;

				printf("\n");

				break;

			case OP_ESCRIBIR: 		
				printf("%s [%02d]: %d\n", MSJ_POS, operand, *(palabra_t *)simpletron->memory->datos[operand]);
				simpletron->pc = k;

				break;								
			
			case OP_CARGAR: 		
				simpletron_op_cargar(simpletron, operand);	
				simpletron->pc = k;

				break;
			
			case OP_GUARDAR:
				vector_op_guardar(simpletron->memory, operand, simpletron->acc);
				simpletron->pc = k;

				break;

			case OP_PCARGAR: 
				simpletron_op_cargarp(simpletron, operand);
				simpletron->pc = k;

				break;

			case OP_PGUARDAR: 
				vector_op_guardarp(simpletron->memory, operand, simpletron->acc);
				simpletron->pc = k;

				break;

			case OP_SUMAR: 
				simpletron_op_sumar(simpletron, operand);
				simpletron->pc = k;

				break;

			case OP_RESTAR:
				simpletron_op_restar(simpletron, operand);
				simpletron->pc = k;

				break;

			case OP_DIVIDIR: 	
				simpletron_op_dividir(simpletron, operand);
				simpletron->pc = k;

				break;

			case OP_MULTIPLICAR: 	
				simpletron_op_multiplicar(simpletron, operand);
				simpletron->pc = k;

				break;

			case OP_JMP: 
				if(simpletron_op_jmp(simpletron->memory, &k, operand) == false)
					return false;

				break;

			case OP_JMPNEG: 
				if(simpletron_op_jmpneg(simpletron, &k, operand) == false)
					return false;

				simpletron->pc = k;
				
				break;

			case OP_JMPZERO: 
				if(simpletron_op_jmpzero(simpletron, &k, operand) == false)
					return false;

				simpletron->pc = k;

				break;

			case OP_JNZ: 
				if(simpletron_op_jmz(simpletron, &k, operand) == false)
					return false;

				break;

			case OP_DJNZ: 		
				simpletron_op_djnz(simpletron, &k, operand);

				simpletron->pc = k;

				break;	

			case OP_HALT: 

				i = 1;

				simpletron->pc = k;	
				
				break;		
										
			default: 

				/*El caso default, es que es un dato por lo que se debe proceder a la proxima instruccion*/

				break;
			}		
		}

	return true;

}


void simpletron_op_cargar(simpletron_t *simpletron, int operand){
	
	/*Carga una palabra de la memoria al acumulador*/

	simpletron->acc = *(palabra_t *)simpletron->memory->datos[operand];

}


void simpletron_op_sumar(simpletron_t *simpletron, int operand){

	/*Suma una palabra al acumulador*/

	simpletron->acc += *(palabra_t *)simpletron->memory->datos[operand];

}


void simpletron_op_restar(simpletron_t *simpletron, int operand){

	/*Resta una palabra al acumulador*/

	simpletron->acc -= *(palabra_t *)simpletron->memory->datos[operand];

}


void simpletron_op_dividir(simpletron_t *simpletron, int operand){

	/*Divide al acumulador por el contenido de la posicion de memoria indicada por el interador "i"*/

	simpletron->acc /= *(palabra_t *)simpletron->memory->datos[operand];	

}


void simpletron_op_multiplicar(simpletron_t *simpletron, int operand){

	/*Multiplicar al acumulador por el contenido de la posicion de memoria indicada por el interador "i"*/

	simpletron->acc *= *(palabra_t *)simpletron->memory->datos[operand];
	
}


bool simpletron_op_jmp(vector_t *v, int *k, int operand){

	/*Salta a la orden especificada*/

	if(operand > v->size)
		return false;

	*k = operand - 1 ;

	return true;

}	


bool simpletron_op_jmpneg(simpletron_t *simpletron, int *k, int operand){

	/*Salta a la orden especificada SOLO SI el acumulador es negativo*/

	if(operand > simpletron->memory->size)
			return false;

	if(simpletron->acc < 0){
		*k = operand - 1 ;
		return true;
	}

	else
		return false;
}


bool simpletron_op_jmpzero(simpletron_t *simpletron, int *k, int operand){

	/*Salta a la orden especificada SOLO SI el acumulador es 0*/

	if(operand > simpletron->memory->size)
		return false;
	
	if(simpletron->acc == 0){
		*k= operand - 1 ;
		return true;
	}

	else
		return false;
}


bool simpletron_op_jmz(simpletron_t *simpletron, int *k, int operand){

	/*Salta a la orden especificada SOLO SI el acumulador es distinto de 0*/

	if(operand > simpletron->memory->size)
		return false;

	if((simpletron->acc)){
		*k = operand - 1;
		return true;
	}

	else
		return false;
}


void simpletron_op_djnz(simpletron_t *simpletron, int *k, int operand){

	/*Decrementa el acumulador por el contenido de la posicion de memoria indicado y, si este no es 0, vuelve al comienzo del ciclo*/

	if((simpletron->acc -= *(palabra_t *)simpletron->memory->datos[operand]) == 0) 
		*k = -1;

}


void simpletron_op_cargarp(simpletron_t *simpletron, int operand){

	/*Es homologa a la funcion cargar, pero se indica una posicion de memoria donde se sacara un puntero*/

	simpletron->acc = *(palabra_t *)simpletron->memory->datos[*(palabra_t *)simpletron->memory->datos[operand]]; 

}