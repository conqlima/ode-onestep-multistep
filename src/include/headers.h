#ifndef _HEADERS_H_
#define _HEADERS_H_
/************************************************************/
/*Insira aqui todas as funções que deseja calcular.
 * F(x,y) representa a equação diferencial na integra
 * Y(x) representa a equação da solução exata da função
 * Abaixo está alguns exemplos de EDOs.
 * 						ATENÇÃO							
 * DEIXE APENAS UM PAR DE MACROS DESCOMENTADOS! */

/*http://asafilho.blogspot.com.br/2015/04/solucao-numerica-de-equacoes_24.html*/
#define F(x,y) ( 1.0 - x + (4.0 * y) ) 
#define Y(x) ( ( 1.0 / 4.0 ) * x - ( 3.0 / 16.0 ) + ( 19.0 / 16.0 ) * exp ( 4.0 * x ) )
//y(0) = 1, no intervalo [0, 2]

/*Algoritmos Numéricos, Frederico Ferreira Campos, filho*/
//#define F(x,y) (x+(-2.0*y)+1.0)
//#define Y(x) ((1.0/4.0)*((3.0*exp(-2.0*x))+(2.0*x)+1.0))
//y(0) = 1, no intervalo [0, 1]

/*Equações diferenciais com aplicações em modelagem, Dennis G. Zill*/
//#define F(x,y) (0.2*x*y)
//#define Y(x) (exp(0.1*(pow(x,2)-1)))
//y(1) = 1, no intervalo [1, 1.5]

/************************************************************/

/*Protótipos das funções do arquivo equation.c*/
long double f ( long double x, long double y );
long double y ( long double x );

/*Protótipos das funções do arquivo util.c*/
void control ( double x0, double y0, int m, double b, char* s, char* nome );
void scrip_gnuplot ( char str[] );

#endif
