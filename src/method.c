#include "include/headers.h"
#include "include/method.h"

//Definiçao do método de runge-kutta de 4a ordem
long double runge_kutta_4 ( long double x, long double y, double h )
{
    long double k1, k2, k3, k4;
    k1 = f ( x, y );
    k2 = f ( x + 0.5 * h, y + 0.5 * h * k1 );
    k3 = f ( x + 0.5 * h, y + 0.5 * h * k2 );
    k4 = f ( x + h, y + h * k3 );
    y = y + h * ( k1 + 2.0 * k2 + 2.0 * k3 + k4 ) / 6.0;
    return y;
}
//Definiçao do método de runge-kutta de 3a ordem
long double runge_kutta_3 ( long double x, long double y, double h )
{
    long double k1, k2, k3;
    k1 = f ( x, y );
    k2 = f ( x + 0.5 * h, y + 0.5 * h * k1 );
    k3 = f ( x + h, y + 2.0 * h * k2 - h * k1 );
    y = y + h * ( k1 + 4.0 * k2 + k3 ) / 6.0;
    return y;
}
//Definiçao do método de euler modificado (Runge-kutta 2a ordem)
long double euler_modificado ( long double x, long double y, double h )
{
    long double k1, k2;
    k1 = f ( x, y );
    k2 = f ( x + 0.5 * h, y + 0.5 * h * k1 );
    y = y + h * k2;
    return y;
}
//Definiçao do método de euler (Runge-Kutta 1a ordem)
long double euler ( long double x, long double y, double h )
{
    long double k1;
    k1 = f ( x, y );
    y = y + h * k1;
    return y;
}
//Definição da equação de Dormand-Prince
long double dopri ( long double x, long double y, double h )
{
    long double k1, k2, k3, k4, k5, k6;
    k1 = h*f ( x,y );
    k2 = h*f ( ( x+ ( 1.0/5.0 ) *h ), ( y+ ( 1.0/5.0 ) *k1 ) );
    k3 = h*f ( ( x+ ( 3.0/10.0 ) *h ), ( y+ ( 3.0/40.0 ) *k1+ ( 9.0/40.0 ) *k2 ) );
    k4 = h*f ( x+ ( 4.0/5.0 ) *h,y+ ( 44.0/45.0 ) *k1+ ( -56.0/15.0 ) *k2+ ( 32.0/9.0 ) *k3 );
    k5 = h*f ( ( x+ ( 8.0/9.0 ) *h ), ( y+ ( 19372.0/6561.0 ) *k1+ ( -25360.0/2187.0 ) *k2+ ( 64448.0/6561.0 ) *k3+ ( -212.0/729.0 ) *k4 ) );
    k6 = h*f ( ( x+1.0*h ), ( y+ ( 9017.0/3168.0 ) *k1+ ( -355.0/33.0 ) *k2+ ( 46732.0/5247.0 ) *k3+ ( 49.0/176.0 ) *k4+ ( -5103.0/18656.0 ) *k5 ) );
    y = ( y + ( ( 35.0/384.0 ) * k1 ) + ( ( 500.0/1113.0 ) * k3 ) + ( ( 125.0/192.0 ) * k4 ) + ( ( -2187.0/6784.0 ) * k5 ) + ( ( 11.0/84.0 ) * k6 ) );
    return y;
}
//Definição da equação de Adams-Bashforth-Moulton de 4ª ordem
long double abm4 ( long double x, long double y[], double h )
{
    long double f0, f1, f2, f3, f4;
    long double yp;
    f0 = f ( x-3.0*h,y[0] );
    f1 = f ( x-2.0*h,y[1] );
    f2 = f ( x-1.0*h,y[2] );
    f3 = f ( x,y[3] );
    yp = y[3] + ( h / 24.0 ) * ( 55.0*f3 - 59.0*f2 + 37.0*f1 - 9.0*f0 );
    f4 = f ( x+h,yp );
    yp = y[3] + ( h / 24.0 ) * ( 9.0*f4 + 19.0*f3 - 5.0*f2 + f1 );
    f4 = f ( x+h,yp );
    yp = y[3] + ( h / 24.0 ) * ( 9.0*f4 + 19.0*f3 - 5.0*f2 + f1 );
    return yp;
}

long double milne ( long double x, long double y[], double h )
{
	long double f0, f1, f2, f3, f4;
	long double yp;
	f0 = f ( x-3.0*h,y[0] );
	f1 = f ( x-2.0*h,y[1] );
	f2 = f ( x-1.0*h,y[2] );
	f3 = f ( x,y[3] );
	yp = y[0] + ((4.0*h)/3.0)*(2*f3 - f2 + 2*f1);
	f4 = f(x+h,yp);
	yp = y[2] + (h/3)*(f4 + 4*f3 + f2);
	return yp;
}

long double hamming ( long double x, long double y[], double h )
{
	long double f0, f1, f2, f3, f4;
	long double yp;
	f0 = f ( x-3.0*h,y[0] );
	f1 = f ( x-2.0*h,y[1] );
	f2 = f ( x-1.0*h,y[2] );
	f3 = f ( x,y[3] );
	yp = y[0] + ((4.0*h)/3.0)*(2.0*f3 - f2 + 2.0*f1);
	f4 = f(x+h,yp);
	yp = (1.0/8.0)*(9*y[3] - y[1]) + ((3.0*h)/8.0)*(f4 + 2*f3 - f2);
	return yp;
}

