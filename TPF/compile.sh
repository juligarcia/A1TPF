gcc -ansi -g -Wall -pedantic -c -o main.o main.c
gcc -ansi -g -Wall -pedantic -c -o misc.o misc.c
gcc -ansi -g -Wall -pedantic -c -o simpletron.o simpletron.c
gcc -ansi -g -Wall -pedantic -c -o lista.o lista.c
gcc -ansi -g -Wall -pedantic -c -o vector.o vector.c
gcc -ansi -g -Wall -pedantic -c -o argument_proc.o argument_proc.c
gcc -Wall -g -o tpfinal main.o misc.o simpletron.o lista.o vector.o argument_proc.o

