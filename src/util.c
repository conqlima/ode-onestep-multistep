#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include "include/method.h"
#include "include/equation.h"
#include "include/util.h"

//#define P 0.0
static FILE *fp;
//FILE* fq;

void control ( double x0, double y0, int m, double b, char* s, char* nome )
{
	//FILE *fp;
    unsigned int i = 0;
    //unsigned long long j = 0.0;
    long double xn = x0;
    double h = ( b - x0 ) /m;
    long double p = 0.0;
    long double yv[4] = {y0,y0,y0,y0};    
    long double yx,y_e, y_em, y_rk3, y_rk4, y_dp, y_abm4;
    y_e = y_em = y_rk3 = y_rk4 = y_dp = y_abm4 = y0;    
    if (((fp = fopen ( nome, "w" )) == NULL) || (s == NULL))
		{
			fprintf(stderr, "não posso abrir ou criar o arquivo %s",nome);
			exit(EXIT_SUCCESS);
		}
	else
    //fq = fopen ( "erro", "w" );
    for ( i = 0; xn < b+h ; xn = xn + h,i++ )
    {
        //print(0,xn,p);
        fprintf(fp, "%.4Le \t ",xn);
        
        //print(xn,y_e,y_em,y_rk3,y_rk4,y_dp,y_abm4,yx,p);
        //fprintf ( fp, "%f \t %.30Le \t %.30Le \t %.30Le \t %.30Le \t %.30Le \t %.30Le \t %.30Le \n", xn, y_e, y_em, y_rk3, y_rk4, y_dp, y_abm4, yx);
        //fprintf ( fp, "%f \t %.4Le \t %.4Le \t %.4Le \t %.4Le \t %.4Le \t %.4Le \t %.4Le \n", xn, y_e, y_em, y_rk3, y_rk4, y_dp, y_abm4, y ( xn ) );
        //fprintf ( fq, "%f \t %.20Le \t %.20Le \t %.20Le \t %.20Le \t %.20Le \t %.20Le \t %.20Le \n", xn,  fabsl ( ( yx - y_e ) ), fabsl ( ( yx - y_em ) ), fabsl ( ( yx - y_rk3 ) ), fabsl ( ( yx - y_rk4 ) ), fabsl ( ( yx - y_dp ) ), fabsl ( ( yx - y_abm4 ) ),fabsl ( ( yx - yx ) ) );
        strstr ( s,"e" ) != NULL ? print(0,y_e,p),( y_e = euler ( xn, y_e, h ) ) : ( y_e = 0 ) ;
        strstr ( s,"rk2" ) != NULL ? print(0,y_em,p),( y_em = euler_modificado ( xn, y_em, h ) ) : ( y_em = 0 ) ;
        strstr ( s,"rk3" ) != NULL ? print(0,y_rk3,p),( y_rk3 = runge_kutta_3 ( xn, y_rk3, h ) ) : ( y_rk3 = 0 ) ;
        strstr ( s,"rk4" ) != NULL ? print(0,y_rk4,p),( y_rk4 = runge_kutta_4 ( xn, y_rk4, h ) ) : ( y_rk4 = 0 ) ;
        strstr ( s,"dp" ) != NULL ? print(0,y_dp,p),( y_dp = dopri ( xn, y_dp, h ) ) : ( y_dp = 0 ) ;
        if ( strstr ( s,"abm4" ) != NULL )
        {
			print(0.0,y_abm4,p);
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
        yx = y ( xn ); 
        print(0,yx,p);
        fprintf(fp,"\n");
    }
    (void)fclose ( fp );
    //fclose ( fq );
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
static void print(double x, ...)
{
	long double y;
	va_list argumentos;
	va_start (argumentos,x);	
	//fp = fopen ( "robson", "w" );
    //fq = fopen ( "erro", "w" );
	//if (x == 0)
	//fprintf(fp,"%f\t",x);
	while((y = va_arg(argumentos,long double)) != 0.0)
	fprintf(fp, "%.4Le \t ",y);
	//fprintf(fp,"\n");
	va_end(argumentos);
	//fclose ( fp );
    //fclose ( fq );
	
}
