#include <stdio.h>
#include <stdlib.h>
#include "include/util.h"
#include "include/equation.h"
#include "include/method.h"

int main ( int argc, char **argv )
{
	if (argc != 6)
	(void)puts("numero de parametros errados");
    else
    control ( atof ( argv[1] ),atof ( argv[2] ),atoi ( argv[3] ),atof ( argv[4] ),argv[5],argv[6] );
    return EXIT_SUCCESS;
}

