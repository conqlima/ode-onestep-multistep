#ifndef _METHOD_H_
#define _METHOD_H_
/*Protótipos das funções*/
long double abm4 ( long double x, long double y[], double h );
long double dopri ( long double x, long double y, double h );
long double runge_kutta_4 ( long double x, long double y, double h );
long double runge_kutta_3 ( long double x, long double y, double h );
long double euler_modificado ( long double x, long double y, double h );
long double euler ( long double x, long double y, double h );
#endif
