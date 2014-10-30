/* Ex. 2-3 $2.7 */
#include <stdio.h>
#include <limits.h>

/* htoi: convert a string of hexical digits to its integer value */
static unsigned htoi(const char *s)
{
  unsigned x, v;

  if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
    s += 2;
  for (x = 0u; (v = *s); s++, x = (x << 4) + v)
    if (v >= '0' && v <= '9')
      v += -'0';
    else if (v >= 'a' && v <= 'f')
      v += -'a' + 10;
    else if (v >= 'A' && v <= 'F')
      v += -'A' + 10;
    else
      break;
  return x;
}

/* htoi2: same as htoi, an alternative version */
static unsigned htoi2(const char *s)
{
#define v(i) val[(i) - CHAR_MIN]
  static int val[1 << CHAR_BIT]={0};
  unsigned x, i;

  if (v('0') == 0) {
    for (i = '0'; i <= '9'; i++) v(i) = i - '0' + 1;
    for (i = 'a'; i <= 'f'; i++) v(i) = i - 'a' + 11;
    for (i = 'A'; i <= 'F'; i++) v(i) = i - 'A' + 11;
  }
  if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
    s += 2;
  for (x = 0u; *s && v(*s); s++)
    x = (x << 4) + v(*s) - 1;
  return x;
}

int main(int argc, char *argv[])
{
  const char *s = "0x7f";
  unsigned i, i2;

  if (argc >= 2) s = argv[1];
  i = htoi(s);
  i2 = htoi2(s);
  printf("htoi(%s) = %u (version 1) %u (version 2)\n", s, i, i2);
  return 0;
}


