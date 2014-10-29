#include <stdio.h>
#include <ctype.h>

#define NUMBER '0'
static int getop(char *s);

int main(void)
{
  char s[128];

  while (getop(s) != EOF) {
    printf("%s\n", s);
  }
  return 0;
}

#define BUFSIZE 100
int getop(char *s)
{
  static char buf[BUFSIZE];
  static int bufp;
  int i, c;

#define getch()   ((bufp > 0) ? buf[--bufp] : getchar())
#define ungetch() if (bufp >= BUFSIZE) fprintf(stderr, "cannot ungetch()\n"); \
  else buf[bufp++] = (char) c;

  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;
  s[1] = '\0';
  if (!isdigit(c) && c != '.') /* operator */
    return c;
  i = 0;
  if (isdigit(c))
    while (isdigit(s[++i] = c = getch()))
      ;
  if (c == '.')
    while (isdigit(s[++i] = c = getch()))
      ;
  s[i] = '\0';
  if (c != EOF) {
    ungetch();
  }
  return NUMBER;
}
