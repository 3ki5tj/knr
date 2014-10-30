#include <stdio.h>
#include <ctype.h>

static int getop(char *s)
{
#define BUFSIZE 100
  static char buf[BUFSIZE];
  static int bufp;
  int i, c;

#define getch()   ((bufp > 0) ? buf[--bufp] : getchar())
#define ungetch() if (bufp >= BUFSIZE) fprintf(stderr, "cannot ungetch()\n"); \
  else buf[bufp++] = (char) c;

  while (s[0] = (char) (c = getch()), c == ' ' || c == '\t')
    ;
  s[1] = '\0';
  if (!isdigit(c) && c != '.') /* operator */
    return c;
  i = 0;
  if (isdigit(c))
    while (s[++i] = (char) (c = getch()), isdigit(c))
      ;
  if (c == '.')
    while (s[++i] = (char) (c = getch()), isdigit(c))
      ;
  s[i] = '\0';
  if (c != EOF) {
    ungetch();
  }
  return '0';
}

int main(void)
{
  char s[128];

  while (getop(s) != EOF)
    printf("%s\n", s);
  return 0;
}

