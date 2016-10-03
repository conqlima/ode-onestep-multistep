#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include "include/method.h"
#include "include/headers.h"
//#include "include/equation.h"
//#include "include/util.h"

static FILE *fp;

static void print(long double y)
{

	fprintf(fp, "%.4Le\t", y);
}

void control ( double x0, double y0, int m, double b, char* s, char* nome )
{
	unsigned int i = 0;
	long double xn = x0;
	/*Calcula o tamanho do passo*/
	double h = ( b - x0 ) / m;
	/*Vetores auxiliares para métodos de passo múltiplo*/
	long double yv_abm4[4] = {y0,y0,y0,y0};
	long double yv_mil[4] = {y0,y0,y0,y0};
	long double yv_ham[4] = {y0,y0,y0,y0};
	long double yx = y0;
	long double y_e = y0;
	long double y_em = y0;
	long double y_rk3 = y0;
	long double y_rk4 = y0;
	long double y_dp = y0;
	long double y_abm4 = y0;
	long double y_mil = y0;
	long double y_ham = y0;
	if (((fp = fopen ( nome, "w" )) == NULL) || (s == NULL))
		{
			fprintf(stderr, "não posso abrir ou criar o arquivo %s",nome);
			exit(EXIT_FAILURE);
		}
	else
	{
		for ( i = 0; i <= m; xn = xn + h,i++ )
		{
			print(xn);
			strstr ( s,"e" ) != NULL ? print(y_e),( y_e = euler ( xn, y_e, h ) ) : ( y_e = 0 ) ;
			strstr ( s,"rk2" ) != NULL ? print(y_em),( y_em = euler_modificado ( xn, y_em, h ) ) : ( y_em = 0 ) ;
			strstr ( s,"rk3" ) != NULL ? print(y_rk3),( y_rk3 = runge_kutta_3 ( xn, y_rk3, h ) ) : ( y_rk3 = 0 ) ;
			strstr ( s,"rk4" ) != NULL ? print(y_rk4),( y_rk4 = runge_kutta_4 ( xn, y_rk4, h ) ) : ( y_rk4 = 0 ) ;
			strstr ( s,"dp" ) != NULL ? print(y_dp),( y_dp = dopri ( xn, y_dp, h ) ) : ( y_dp = 0 ) ;
			if ( strstr ( s,"abm4" ) != NULL )
			{
				print(y_abm4);
				/*O método abm4 necessita de 4 valores anteriores já
				 * calculados por outro método, aqui usamos
				 * o método de dopri para calcular esses valores*/
				if ( xn < 4*h+x0 )
				{
					y_abm4 = dopri ( xn, y_abm4, h );
					yv_abm4[i] = y_abm4;
				}
				else
				{
					y_abm4 = abm4 ( xn,yv_abm4,h );
					yv_abm4[0] = yv_abm4[1];
					yv_abm4[1] = yv_abm4[2];
					yv_abm4[2] = yv_abm4[3];
					yv_abm4[3] = y_abm4;
				}
			}
			else
			y_abm4 = 0;
			/**-----------------------------**/
			if ( strstr ( s,"mil" ) != NULL )
			{
				print(y_mil);
				/*O método mil necessita de 4 valores anteriores já
				 * calculados por outro método, aqui usamos
				 * o método de rk4 para calcular esses valores*/
				if ( xn < 4*h+x0 )
				{
					y_mil = runge_kutta_4 ( xn, y_mil, h );
					yv_mil[i] = y_mil;
				}
				else
				{
					y_mil = milne ( xn,yv_mil,h );
					yv_mil[0] = yv_mil[1];
					yv_mil[1] = yv_mil[2];
					yv_mil[2] = yv_mil[3];
					yv_mil[3] = y_mil;
				}
			}
			else
			y_mil = 0;
			
			/**-----------------------------**/
			if ( strstr ( s,"ham" ) != NULL )
			{
				print(y_ham);
				/*O método ham necessita de 4 valores anteriores já
				 * calculados por outro método, aqui usamos
				 * o método de rk4 para calcular esses valores*/
				if ( xn < 4*h+x0 )
				{
					y_ham = runge_kutta_4 ( xn, y_ham, h );
					yv_ham[i] = y_ham;
				}
				else
				{
					y_ham = hamming ( xn,yv_ham,h );
					yv_ham[0] = yv_ham[1];
					yv_ham[1] = yv_ham[2];
					yv_ham[2] = yv_ham[3];
					yv_ham[3] = y_ham;
				}
			}
			else
			y_ham = 0;
			
			/*Solução Exata da função y(x)*/
			yx = y ( xn );
			print(yx);
			fprintf(fp,"\n");
		}
	}
	(void)fclose ( fp );
	//scrip_gnuplot ( nome );
	//system ( "gnuplot script.plt" );
}
//void scrip_gnuplot ( char str[25] )
//{
	//fp = fopen ( "script.plt", "w" );
	//fprintf ( fp, "reset\n" );
	//fprintf ( fp, "set title \"Metodos de Runge Kutta\" \n" );
	//fprintf ( fp, "set xlabel \"Xn\" \n" );
	//fprintf ( fp, "set ylabel \"Yn\" \n" );
	//fprintf ( fp, "set key left \n" );
	//fprintf ( fp, "set term jpeg \n" );
	//fprintf ( fp, "set output \"graph.jpeg\" \n" );
	//fprintf ( fp, "plot \'%s\' u 1:2 t \" Euler \" w lp ls 7 lc 1 lw 1, \'%s\' u 1:3 t \" Euler Modificado \" w lp ls 7 lc 2 lw 1,", str, str );
	//fprintf ( fp, "\'%s\' u 1:4 t \" Runge-Kutta 3a ordem \" w lp ls 7 lc 4 lw 1, \'%s\' u 1:5 t \" Runge-Kutta 4a ordem \" w lp ls 7 lc 5 lw 1, \'%s\' u 1:6 t \" Dormand-Prince \" w lp ls 7  lc 6 lw 1, \'%s\' u 1:7 t \" Analitica \" w lp ls 3 lc -1 lw 1 \n", str, str, str, str );
	//fprintf ( fp, "replot \n" );
	//fprintf ( fp, "pause -1 \"Continuar?\" " );
	//fclose ( fp );
//}
