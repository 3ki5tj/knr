/* Ex. 2-1 $2.2 */
#include <stdio.h>
#include <limits.h>
#include <float.h>

#define WID 24

#define cat_(a, b)  a ## b
#define cat(a, b)   cat_(a, b)

/* print the limits of an integral data type from <limits.h> */
#define pih(TYPE) \
  printf("%-11s: min %-*ld max %-*ld unsigned max %-*lu\n", \
    (# TYPE), WID, (long) cat(TYPE, _MIN), WID, \
                   (long) cat(TYPE, _MAX), WID, \
                   (unsigned long) cat(cat(U, TYPE), _MAX))

/* print the limits of a floating-point data type from <float.h> */
#define pfh(TYPE) \
  printf("%-11s: min %-*.*Le max %-*.*Le\n", \
    (# TYPE), WID, WID - 8, (long double) cat(TYPE, _MIN), \
              WID, WID - 8, (long double) cat(TYPE, _MAX))

/* print the limits of an integral data type directly */
#define pic(type)                                             \
{                                                             \
  type imax = (type) ( (unsigned type) (~0u) >> 1 );          \
  type imin = (type) ( imax + '\01' );                        \
  printf("%-11s: min %-*ld max %-*ld unsigned max %-*lu\n",   \
    (# type), WID, (long) imin, WID, (long) imax, WID,        \
      (unsigned long) (unsigned type) (-1));                  \
}

/* print the limits of a floating-point data type directly */
#define pfc(type)                                             \
{                                                             \
  type f = 1.0f, g, a, inf, fltmin, fltmax;                   \
  for (inf = f; inf < inf + inf; inf *= 100.0) f = inf;       \
  for (a = f, g = inf; a > 0.0 && g >= inf; a *= 0.5)         \
    /* test if adding a changes f */                          \
    for (; (g = f + a) < inf && f < g; f = g) ;               \
  fltmax = f;                                                 \
  for (f = 1.0f; (g = f*.5f) > (type) 0.0; f *= 0.5) ;        \
  fltmin = f;                                                 \
  printf("%-11s: min %-*.*Le max %-*.*Le\n",                  \
    (# type), WID, WID - 8, (long double) fltmin,             \
              WID, WID - 8, (long double) fltmax);            \
}

int main(void)
{
  printf("Values determined from <limits.h> and <float.h>:\n");
  pih(CHAR);
  pih(SHRT);
  pih(INT);
  pih(LONG);
  pfh(FLT);
  pfh(DBL);
  pfh(LDBL);
  puts("");

  printf("Values determined from direct computation:\n");
  pic(char);
  pic(short);
  pic(int);
  pic(long);
  pfc(float);
  pfc(double);
  pfc(long double);
  puts("");

  return 0;
}

