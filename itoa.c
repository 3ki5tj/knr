/* Ex. 3-4, 3-5 and 3-6 $3.6 */
#include <stdio.h>

#define itoa(n,s)    itobw(n,s,10u,0u) /* Ex. 3-4 */
#define itob(n,s,b)  itobw(n,s,b,0u)   /* Ex. 3-5 */
#define itoaw(n,s,w) itobw(n,s,10u,w)  /* Ex. 3-6 */

/* itobw: print n in base b with padding blanks to w character wide to s */
static void itobw(int n, char *s, unsigned b, int w)
{
  int sign, i, j, c;
  unsigned u;

  if (n < 0) {
    sign = 1;
    u = (n - 1 > 0) ? (unsigned)(-(n + 1)) + 1u : -n;
  } else {
    u = n;
  }
  i = 0;
  do {
    c = u % b;
    s[i++] = (char)( (c >= 10) ? c - 10+'a' : c+'0' );
  } while ((u /= b) > 0);
  if (sign)
    s[i++] = '-';
  while (i < w) /* add padding blanks */
    s[i++] = ' ';
  s[i--] = '\0';
  for (j = 0; j < i; j++, i--) /* reverse the string */
    c = s[j], s[j] = s[i], s[i] = (char) c;
}

int main(void)
{
  int n = (int)(~(~0u>>1)), base = 16;
  char buf[32];

  itoa(n, buf);
  printf("n=%d itoa(n, buf) [%s]\n", n, buf);
  itob(n, buf, base);
  printf("n=%d itob(n, buf, %d)  [%s]\n", n, base, buf);
  itoaw(n, buf, 16);
  printf("n=%d itoa_pad(n, buf, 16) [%s]\n", n, buf);
  itoaw(n, buf, 6);
  printf("n=%d itoa_pad(n, buf, 6) [%s]\n", n, buf);
  return 0;
}

