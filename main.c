#include <stdlib.h>
#include "util.h"
#include "equation.h"
#include "method.h"

int main ( int argc, char **argv )
{
    control ( atof ( argv[1] ),atof ( argv[2] ),atoi ( argv[3] ),atof ( argv[4] ),argv[5],argv[6] );
    return EXIT_SUCCESS;
}

