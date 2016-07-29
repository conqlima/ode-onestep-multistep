#ifndef _EQUATION_H_
#define _EQUATION_H_
/*Insira aqui todas as funções que deseja calcular*/

//#define F(x,y) ( 1.0 - x + (4.0 * y) )
//#define Y(x) ( ( 1.0 / 4.0 ) * x - ( 3.0 / 16.0 ) + ( 19.0 / 16.0 ) * exp ( 4.0 * x ) )

#define F(x,y) (x+(-2.0*y)+1.0)
#define Y(x) ((1.0/4.0)*((3.0*exp(-2.0*x))+(2.0*x)+1.0))

/*Protótipos das funções*/
long double f ( long double x, long double y );
long double y ( double x );
#endif
