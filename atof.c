/* Ex. 4-2 $4.2 */
#include <stdio.h>

static double atof(const char *s);

int main(int argc, char *argv[])
{
  char *s = "123.45e-6";
  double x;

  if (argc >= 2)
    s = argv[1];
  x = atof(s);
  printf("atof(%s)=%.14e\n", s, x);
  return 0;
}

#include <ctype.h>

/* atof: convert string s to double */
double atof(const char *s)
{
  double val, power;
  int sign, psign, e;

  while (isspace(*s))
    s++;
  sign = (*s == '-') ? -1 : 1;
  if (*s == '-' || *s == '+')
    s++;
  for (val = 0.0; isdigit(*s); s++)
    val = val * 10.0 + *s - '0';
  if (*s == '.')
    s++;
  for (power = 1.0; isdigit(*s); s++, power *= 0.1)
    val = val * 10.0 + *s - '0';
  if (*s == 'e' || *s == 'E')
    s++;
  psign = (*s == '-') ? -1 : 1;
  if (*s == '-' || *s == '+')
    s++;
  for (e = 0; isdigit(*s); s++)
    e = e * 10 + *s - '0';
  for (; e; e--)
    power *= psign > 0 ? 10.0 : 0.1;
  return sign * val * power;
}
