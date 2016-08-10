#ifndef _UTIL_H_
#define _UTIL_H_
//extern FILE *fp;
/*Protótipos das funções*/
void control ( double x0, double y0, int m, double b, char* s, char* nome );
void scrip_gnuplot ( char str[] );
static void print(double x, ...);
#endif
