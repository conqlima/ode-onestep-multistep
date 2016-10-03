#include <math.h>
#include "include/headers.h"
//#include "include/equation.h"
/*Definição da equação diferencial: dy/dx=f(x,y)*/
long double f ( long double x, long double y )
{
    /*Insira o nome da macro que representa a função F(x,y) que deseja calcular*/
    return F ( x,y );
}
/*Definiçao da solução analitica da equação diferencial*/
long double y ( long double x )
{
    /*Insira o nome da macro que representa a função y(x) analítica que deseja calcular*/
    return Y ( x );
}
