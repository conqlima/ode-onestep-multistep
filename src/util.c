#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include "include/method.h"
#include "include/headers.h"

static FILE* fr;
static FILE* fer;
int ncoluna[9];


static int coluna (int n)
{
	int i = 0;
	int j = 0;
	if (n == 0)
	return 2;
	else
	for (i = n; i >= 0; i--)
	{
		j = ncoluna[i] + j;
	}
	return (j+1);
}

static void quebrar_linha()
{
	fprintf(fr,"\n");
	fprintf(fer,"\n");
}

static void erro_porcentual(long double a, long double b)
{
	fprintf(fer, "%.4Le\t", fabsl(((a-b)/b)*100.00));
}

static void print(long double y)
{

	fprintf(fr, "%.6LF\t", y);
}

void control ( double x0, double y0, int m, double b, char* s, char* nome )
{
	unsigned int i = 0;
	//int j[8] = 0;
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
	if (((fr = fopen ( nome, "w" )) == NULL) || ((fer = fopen ( "erro-porcentual.txt", "w" )) == NULL))
	{
		fprintf(stderr, "não posso abrir ou criar o arquivo %s\n",nome);
		exit(EXIT_FAILURE);
	}
	else
	{
		for ( i = 0; i <= m; xn = xn + h,i++ )
		{			
			print(xn);
			/*Calcula a solução exata da função y(x)*/
			if (strstr(s, "y") != NULL)
			{
				yx = y ( xn );
				ncoluna[8] = 1;
			}
			else
			yx = 0;			
			strstr ( s,"e" ) != NULL ? print(y_e),ncoluna[0] = 1,erro_porcentual(y_e,yx),( y_e = euler ( xn, y_e, h ) ) : ( y_e = 0 ) ;
			strstr ( s,"rk2" ) != NULL ? print(y_em),ncoluna[1] = 1,erro_porcentual(y_em,yx),( y_em = euler_modificado ( xn, y_em, h ) ) : ( y_em = 0 ) ;
			strstr ( s,"rk3" ) != NULL ? print(y_rk3),ncoluna[2] = 1,erro_porcentual(y_rk3,yx),( y_rk3 = runge_kutta_3 ( xn, y_rk3, h ) ) : ( y_rk3 = 0 ) ;
			strstr ( s,"rk4" ) != NULL ? print(y_rk4),ncoluna[3] = 1,erro_porcentual(y_rk4,yx),( y_rk4 = runge_kutta_4 ( xn, y_rk4, h ) ) : ( y_rk4 = 0 ) ;
			strstr ( s,"dp" ) != NULL ? print(y_dp),ncoluna[4] = 1,erro_porcentual(y_dp,yx),( y_dp = dopri ( xn, y_dp, h ) ) : ( y_dp = 0 ) ;
			if ( strstr ( s,"abm4" ) != NULL )
			{
				ncoluna[5] = 1;
				print(y_abm4);
				erro_porcentual(y_abm4,yx);
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
				ncoluna[6] = 1;
				print(y_mil);
				erro_porcentual(y_mil,yx);
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
				ncoluna[7] = 1;
				print(y_ham);
				erro_porcentual(y_ham,yx);
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
			/*Imprimir solução exata da função*/
			print(yx);
			quebrar_linha();
		}
	}
	(void)fclose ( fr );
	scrip_gnuplot ( nome );
	system ( "gnuplot script.plt" );
}

void scrip_gnuplot ( char str[25] )
{
	FILE* fp;
	if ((fp = fopen ( "script.plt", "w" )) == NULL)
	{
		fprintf(stderr, "não posso abrir ou criar o arquivo %s\n",str);
		exit(EXIT_FAILURE);
	}
	fprintf ( fp, "reset\n" );
	fprintf ( fp, "set title \"Metodos de resolução de EDOs\" \n" );
	fprintf ( fp, "set xlabel \"Xn\" \n" );
	fprintf ( fp, "set ylabel \"Yn\" \n" );
	fprintf ( fp, "set key left \n" );
	fprintf ( fp, "set term pdf \n" );
	fprintf ( fp, "set output \"graph.pdf\" \n" );
	fprintf ( fp, "plot ");
	if (ncoluna[0] == 1)
	fprintf ( fp, "\'%s\' u 1:%d t \" Euler \" w lp ls 7 lc 1 lw 1,", str,coluna(0));
	if (ncoluna[1] == 1)
	fprintf ( fp, "\'%s\' u 1:%d t \" Euler Modificado \" w lp ls 7 lc 2 lw 1,", str,coluna(1) );
	if (ncoluna[2] == 1)
	fprintf ( fp, "\'%s\' u 1:%d t \" Runge-Kutta 3a ordem \" w lp ls 7 lc 3 lw 1,", str,coluna(2) );
	if (ncoluna[3] == 1)
	fprintf ( fp, "\'%s\' u 1:%d t \" Runge-Kutta 4a ordem \" w lp ls 7 lc 4 lw 1,", str,coluna(3) );
	if (ncoluna[4] == 1)
	fprintf ( fp, "\'%s\' u 1:%d t \" Dormand-Prince \" w lp ls 7  lc 5 lw 1,", str,coluna(4) );
	if (ncoluna[5] == 1)
	fprintf ( fp, "\'%s\' u 1:%d t \" Adams-Bashforth-Moulton de 4ª ordem \" w lp ls 7  lc 6 lw 1,", str,coluna(5) );
	if (ncoluna[6] == 1)
	fprintf ( fp, "\'%s\' u 1:%d t \" Milne \" w lp ls 7  lc 7 lw 1,", str,coluna(6) );
	if (ncoluna[7] == 1)
	fprintf ( fp, "\'%s\' u 1:%d t \" Hamming \" w lp ls 7  lc 8 lw 1,", str,coluna(7) );
	if (ncoluna[8] == 1)
	fprintf ( fp, "\'%s\' u 1:%d t \" Analitica \" w lp ls 3 lc -1 lw 1 \n", str,coluna(8) );
	fprintf ( fp, "replot \n" );
	fprintf ( fp, "pause -1 \"Continuar?\" " );
	fclose ( fp );
}
