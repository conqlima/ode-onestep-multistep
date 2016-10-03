#include <stdio.h>
#include <stdlib.h>
//#include "include/util.h"
//#include "include/equation.h"
#include "include/headers.h"
#include "include/method.h"

int main ( int argc, char **argv )
{
	if (argc != 7){
	(void)puts("Utilização:\n"
	"./main <a> <y0> <m> <b> [nome metodo1, nome metodo2,...] <nome do arquivo>");
	(void)puts("Opções: \n"
	"\ta - valor inicial do intervalo\n"
	"\ty0 - condição inicial do problema\n"
	"\tm - numero de subintervalos desejados\n"
	"\tb - valor final do intervalo\n"
	"\tnome do arquivo - nome do arquivo com os resultados\n");
	(void)puts("Métodos:\n"
	"\te - Euler\n"
	"\trk2 - Runge-Kutta ordem 2\n"
	"\trk3 - Runge-Kutta ordem 3\n"
	"\trk4 - Runge-Kutta ordem 4\n"
	"\tabm4 - Adams-Bashforth-Moulton ordem 4\n"
	"\tdp - Dormand-Prince\n"
	"\tmil - Milne\n"
	"\tham - Hamming\n");
	(void)puts("Exemplo de uso:\n"
	"\t./main 0 1 10 1 e,abm4,mil,ham out.txt");
	}
    else
    control ( atof ( argv[1] ),atof ( argv[2] ),atoi ( argv[3] ),atof ( argv[4] ),argv[5],argv[6] );
    return EXIT_SUCCESS;
}

