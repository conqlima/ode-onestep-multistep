#include "include/equation.h"
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

/*
//Definição da equação de Adams-Bashforth-Moulton de 4ª ordem
long double abm4 ( double x, long double y[], double h )
{
    long double f0, f1, f2, f3, f4;
    f0 = f ( x-3.0*h,y[0] );
    f1 = f ( x-2.0*h,y[1] );
    f2 = f ( x-1.0*h,y[2] );
    f3 = f ( x,y[3] );
    long double yp;
    long double yc;
    //yp = y[3] + h * (55.0*f(x-0.0*h,y[3]) - 59.0*f(x-1.0*h,y[2]) + 37.0*f(x-2.0*h,y[1]) - 9.0*f(x-3.0*h,y[0])) / 24.0;
    yp = y[3] + ( h / 24.0 ) * ( 55.0*f3 - 59.0*f2 + 37.0*f1 - 9.0*f0 );
    f4 = f ( x+h,yp );
    //f4 = f(x,yp);
    //correção
    //yp = y[3] + ((h * (9.0*f(x+1.0*h,yp) + 19.0*f(x-0.0*h,y[3]) - 5.0*f(x-1.0*h,y[2]) + f(x-0.0*h,y[1]))) / 24.0);
    yc = y[3] + ( h / 24.0 ) * ( 9.0*f4 + 19.0*f3 - 5.0*f2 + f1 );
    yp = yc;
    f4 = f ( x+h,yp );
    //f4 = f(x,yp);
    //yp = y[3] + ((h * (9.0*f(x+1.0*h,yp) + 19.0*f(x-0.0*h,y[3]) - 5.0*f(x-1.0*h,y[2]) + f(x-0.0*h,y[1]))) / 24.0);
    yc = y[3] + ( h / 24.0 ) * ( 9.0*f4 + 19.0*f3 - 5.0*f2 + f1 );
    //long double erro = fabsl(yc-yp)*19.0/270.0;
    return yc;
}*/



/*
//Definição da equação de Dormand-Prince
long double dopri ( double x, long double y, double h )
{
    long double k1, k2, k3, k4, k5, k6;
    k1 = h*f ( x,y );
    k2 = h*f ( ( x+ ( 1.0/5.0 ) *h ), ( y+ ( 1.0/5.0 ) *k1 ) );
    //k2 = h*f(fma((1.0/5.0),h,x),fma((1.0/5.0),k1,y));
    //k2 = h*f((x+(0.2)*h),(y+(0.2)*k1));
    k3 = h*f ( ( x+ ( 3.0/10.0 ) *h ), ( y+ ( 3.0/40.0 ) *k1+ ( 9.0/40.0 ) *k2 ) );
    //k3 = h*f(fma((3.0/10.0),h,x),fma((3.0/40.0),k1,fma((9.0/40.0),k2,y)));
    //k3 = h*f((x+(0.3)*h),(y+(0.075)*k1+(0.225)*k2));
    k4 = h*f ( x+ ( 4.0/5.0 ) *h,y+ ( 44.0/45.0 ) *k1+ ( -56.0/15.0 ) *k2+ ( 32.0/9.0 ) *k3 );
    //k4 = h*f(fma((4.0/5.0),h,x),fma((44.0/45.0),k1,fma((-56.0/15.0),k2,fma((32.0/9.0),k3,y ))));
    //k4 = h*f(x+(0.8)*h,y+(0.977777777)*k1+(-3.733333333)*k2+(3.555555556)*k3);
    k5 = h*f ( ( x+ ( 8.0/9.0 ) *h ), ( y+ ( 19372.0/6561.0 ) *k1+ ( -25360.0/2187.0 ) *k2+ ( 64448.0/6561.0 ) *k3+ ( -212.0/729.0 ) *k4 ) );
    //k5 = h*f(fma((8.0/9.0),h,x),fma((19372.0/6561.0),k1,fma((-25360.0/2187.0),k2,fma((64448.0/6561.0),k3,fma((-212.0/729.0),k4,y)))));
    //k5 = h*f((x+(0.888888888)*h),(y+(2.952598689)*k1+(-11.59579332)*k2+(9.822892852)*k3+(-0.290809327)*k4));
    k6 = h*f ( ( x+1.0*h ), ( y+ ( 9017.0/3168.0 ) *k1+ ( -355.0/33.0 ) *k2+ ( 46732.0/5247.0 ) *k3+ ( 49.0/176.0 ) *k4+ ( -5103.0/18656.0 ) *k5 ) );
    //k6 = h*f(fma(1.0,h,x),fma((9017.0/3168.0),k1,fma((-355.0/33.0),k2,fma((46732.0/5247.0),k3,fma((49.0/176.0),k4,fma((-5103.0/18656.0),k5,y))))));
    //k6 = h*f((x+1*h),(y+(2.846275253)*k1+(-10.75757576)*k2+(8.906422718)*k3+(0.27840909)*k4+(-0.273531303)*k5));
    //k7 = h*f(x+1*h,y+(35/384)*k1+(500/1113)*k3+(125/192)*k4+(-2187/6784)*k5+(11/84)*k6);
    y = ( y + ( ( 35.0/384.0 ) * k1 ) + ( ( 500.0/1113.0 ) * k3 ) + ( ( 125.0/192.0 ) * k4 ) + ( ( -2187.0/6784.0 ) * k5 ) + ( ( 11.0/84.0 ) * k6 ) );
    //y = fma((35.0/384.0), (double)k1, fma((500.0/1113.0), (double)k3, fma((125.0/192.0), (double)k4,fma((-2187.0/6784.0), (double)k5, fma((11.0/84.0), (double)k6, y)))));
    //y = (y + ((0.091145833) * k1) + ((0.449236298) * k3) + ((0.651041666) * k4) + ((-0.322376179) * k5) + ((0.130952381) * k6));
    return y;
}*/