/* Ex. 2-1 $2.2 */
#include <stdio.h>
#include <limits.h>
#include <float.h>

#define WID 24

#define cat_(a,b) a ## b
#define cat(a,b) cat_(a,b)
#define pih(T) printf("%-6s: min=%-*ld and max=%-*ld unsigned max=%-*lu\n", \
    (# T), WID, (long)cat(T,_MIN), WID, (long)cat(T,_MAX), WID, (unsigned long)cat(cat(U, T), _MAX))
#define pfh(T) printf("%-6s: min=%-*.*e and max=%-*.*e\n", \
    (# T), WID, WID-8, cat(T,_MIN), WID, WID-8, cat(T,_MAX))

#define pic(t)                                                 \
{                                                              \
  t imax=(t)( (unsigned t)(~0u)>>1 );                          \
  t imin=(t)( imax+'\01' );                                    \
  printf("%-6s: min=%-*ld and max=%-*ld unsigned max=%-*lu\n", \
    (# t), WID, (long)imin, WID, (long)imax, WID,              \
      (unsigned long)(unsigned t)(-1));                        \
}

#define pfc(t)                                                 \
{                                                              \
  t f=1.0f,g,a,inf,fltmin,fltmax;                              \
  for (inf = f; inf < inf+inf; inf *= 100.0) f = inf;          \
  for (a = f,g = inf; a > 0.0 && g >= inf; a *= 0.5)           \
    /* test if adding a changes f */                           \
    for (; (g=f+a) < inf && f < g; f = g) ;                    \
  fltmax = f;                                                  \
  for (f = 1.0f; (g=f*.5f) > (t)0.0; f *= 0.5) ;               \
  fltmin = f;                                                  \
  printf("%-6s: min=%-*.*e and max=%-*.*e\n",                  \
    (# t), WID, WID-8, fltmin, WID, WID-8, fltmax);            \
}

int main(void)
{
  printf("Values determined from headers:\n");
  pih(CHAR);
  pih(SHRT);
  pih(INT);
  pih(LONG);
  pfh(FLT);
  pfh(DBL);

  printf("Values determined from direct computation:\n");
  pic(char);
  pic(short);
  pic(int);
  pic(long);
  pfc(float);
  pfc(double);

  return 0;
}

