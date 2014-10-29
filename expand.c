/* Ex. 3-3 $3.5 */
#include <stdio.h>

static void expand(const char *s1, char *s2);
static void expand0(const char *s1, char *s2);

/* try a-z, a-b-c, a-z0-9, -a-z, and -a-b-A--c-9-5-0-2-4-- as input */
#define SIZE 256
int main(int argc, char *argv[])
{
  char *src = "a-z0-9", s0[SIZE] = "", s1[SIZE] = "";

  if (argc > 1) src = argv[1];
  expand0(src, s0);
  expand(src, s1);
  printf("s1: %s\ns2: %-60s\n    %-60s (version 0)\n", src, s1, s0);
  return 0;
}

#include <ctype.h>
#include <limits.h>

static int table[1u << CHAR_BIT];
#define tp(c) table[(c) - CHAR_MIN]
#define install_table() if (tp('a') == 0) {                 \
  for (c = 'a'; c <= 'z'; c++) if (isalpha(c)) tp(c) = 'a'; \
  for (c = 'A'; c <= 'Z'; c++) if (isalpha(c)) tp(c) = 'A'; \
  for (c = '0'; c <= '9'; c++) if (isdigit(c)) tp(c) = '0'; }

/* expand: complete shorthand notations like a-c in s1 to abc in s2 */
void expand(const char *s1, char *s2)
{
  int c, cp, sgn;

  install_table();
  for (cp = 0; (c = *s2++ = *s1++); cp = tp(c) ? c : 0)
    if (c == '-' && cp && tp(c = *s1) == tp(cp))
      for (s1++, s2 -= 2, sgn = (c > cp) ? 1 : -1;
          *s2++ = (char) cp, (c - cp)*sgn > 0; cp += sgn)
        ; /* s2 -= 2 is the key to support A-A */
}

/* expand0: simpler version that does not support z-a */
void expand0(const char *s1, char *s2)
{
  int c, cp;

  install_table();
  for (cp = 0; (c = *s2++ = *s1++); cp = tp(c) ? c : 0)
    if (c == '-' && cp && tp(c = *s1) == tp(cp) && cp <= c)
      for (s1++, s2 -= 2; (*s2++ = (char) cp++) < c; )
        ;
}

