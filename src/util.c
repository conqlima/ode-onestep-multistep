#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include "include/method.h"
#include "include/equation.h"
#include "include/util.h"

static FILE *fp;

static void print(long double y)
{

	fprintf(fp, "%.4Le\t", y);
}

static void aux()
{
	
}

void control ( double x0, double y0, int m, double b, char* s, char* nome )
{
    unsigned int i = 0;
    long double xn = x0;
    /*Calcula o tamanho do passo*/
    double h = ( b - x0 ) / m;
    long double yv[4] = {y0,y0,y0,y0};
    long double yx,y_e, y_em, y_rk3, y_rk4, y_dp, y_abm4, y_mil, y_ham;
    y_e = y_em = y_rk3 = y_rk4 = y_dp = y_abm4 = y_mil = y_ham = y0;    
    if (((fp = fopen ( nome, "w" )) == NULL) || (s == NULL))
		{
			fprintf(stderr, "não posso abrir ou criar o arquivo %s",nome);
			exit(EXIT_SUCCESS);
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
			 * calculado por outro método para funcionar, aqui usamos
			 * o método de dopri para calcular esses valores*/
            if ( xn < 4*h+x0 )
            {
                y_abm4 = dopri ( xn, y_abm4, h );
                yv[i] = y_abm4;
            }
            else
            {
                y_abm4 = abm4 ( xn,yv,h );
                yv[0] = yv[1];
                yv[1] = yv[2];
                yv[2] = yv[3];
                yv[3] = y_abm4;
            }
            
        }
        else
        y_abm4 = 0;
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
