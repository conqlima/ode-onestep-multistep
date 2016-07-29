#ifndef _METHOD_H_
#define _METHOD_H_
/*Protótipos das funções*/
long double abm4 ( double x, long double y[], double h );
long double dopri ( double x, long double y, double h );
double runge_kutta_4 ( double x, double y, double h );
double runge_kutta_3 ( double x, double y, double h );
double euler_modificado ( double x, double y, double h );
double euler ( double x, double y, double h );
#endif
