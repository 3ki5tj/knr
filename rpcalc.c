#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define OPSIZE  256
enum{
NUMBER   = '0',
NEG      = '~',  /* negative sign */
PEEK     = '?',  /* peek top without popping */
SWAP     = '$',  /* swap the top two operators */
CLEAR    = '!',  /* clear the stack */
ASSIGN   = '=',  /* assignment */
VAR      = 'a',  /* variable */
RECENT   = '#',  /* recent variable */
MATH0    = 1000, /* mathematical constants */
MATH1    = 1001, /* mathematical functions take one argument */
MATH2    = 1002, /* mathematical functions take two arguments */
};

static int varid = -1;
static double vars[128]; /* variables */

static int mathid = -1;
#define recf0(a) { 0, # a, M_##a,   NULL, NULL}
#define recf1(a) { 1, # a,   0.0,      a, NULL}
#define recf2(a) { 2, # a,   0.0,   NULL,    a}
struct {
  size_t nargs;
  char  *name;
  double val;
  double (*func1)(double);
  double (*func2)(double, double);
} math[] = {   recf0(PI),    recf0(E),     recf1(fabs), recf1(sqrt),
  recf1(sin),  recf1(cos),   recf1(tan),   recf1(asin), recf1(acos),  recf1(atan),
  recf1(exp),  recf1(log),   recf1(log10), recf1(sinh), recf1(acosh), recf1(atanh),
  recf2(fmod), recf2(atan2), recf2(pow),   {0} };

static int getop(char *);
static void push(double);
#define pop()  popx(1)
#define peek() popx(0)
static double popx(int);
static void clearstack(void);

/* reverse Polish calculator */
int main(void)
{
  int type;
  double x, y;
  char s[OPSIZE];

  while ((type = getop(s)) != EOF) {
    switch (type) {
    case NUMBER:
      push(atof(s));
      break;
    case VAR:
      push(vars[varid]);
      break;
    case '+':
      y = pop();
      push(pop() + y);
      break;
    case '*':
      y = pop();
      push(pop() * y);
      break;
    case '-':
      y = pop();
      push(pop() - y);
      break;
    case '/':
      y = pop();
      if (y != 0.0)
        push(pop() / y);
      else
        printf("error: divided by zero\n");
      break;
    case '%':
      y = pop();
      if (y != 0.0)
        push( fmod(x, y) );
      else
        printf("error: divided by zero\n");
      break;
    case MATH0:
      push( math[mathid].val );
      break;
    case MATH1:
      x = pop();
      push( (*math[mathid].func1)(x) );
      break;
    case MATH2:
      y = pop();
      x = pop();
      push( (*math[mathid].func2)(x, y) );
      break;
    case ASSIGN:
      pop();
      vars[varid] = peek();
      break;
    case PEEK:
      printf("\t%.15g\n", vars[RECENT] = peek());
      break;
    case SWAP:
      y = pop();
      x = pop();
      push(y);
      push(x);
      break;
    case CLEAR:
      clearstack();
      break;
    case '\n':
      printf("\t%.15g\n", vars[RECENT] = pop());
      break;
    default:
      printf("error: unknown symbol %s\n", s);
      break;
    }
  }
  return 0;
}

#define STACKSIZE 128
int sp = 0;  /* current free position in the stack */
double val[STACKSIZE];

/* push a value to the stack */
void push(double x)
{
  if (sp >= STACKSIZE)
    printf("error: stack is full, cannot push %g\n", x);
  else
    val[sp++] = x;
}

/* pop the top value from the stack */
double popx(int poptop)
{
  if (sp > 0)
    if (poptop)
      return val[--sp];
    else
      return val[sp - 1];
  else {
    printf("error: stack is empty\n");
    return 0.0;
  }
}

void clearstack(void)
{
  for (sp = STACKSIZE; sp > 0; )
    val[--sp] = 0.0;
  printf("stack is cleared\n");
}

#include <ctype.h>
#include <string.h>

#define GCBUFSIZE 128
static int gcstack[GCBUFSIZE];
static int gcp;

/* pop from gcstack, or get char from stdin */
static int getch(void)
{
  return gcp > 0 ? gcstack[--gcp] : fgetc(stdin);
}

/* push a character back gcstack */
static void ungetch(int c)
{
  if (gcp >= GCBUFSIZE)
    printf("ungetch, stack is full cannot unget\n");
  else
    gcstack[gcp++] = c;
}

static int getmathid(char *s)
{
  int i;
  for (i = 0; math[i].name != NULL; i++)
    if (strcmp(math[i].name, s) == 0)
      return mathid = i;
  return -1;
}

static int isvar(char *s)
{
  if (s[1] == '\0') {
    if (isalpha(s[0]))
      return varid = tolower(s[0]);
    else if (s[0] == RECENT)
      return varid = RECENT;
  }
  return 0;
}

/* getop: get the next operator or number */
int getop(char *s)
{
  int i, c, cn;

  while ((c = getch()) == ' ' || c == '\t' || c =='\r')
    ;
  s[0] = (char) c;
  s[1] = '\0'; /* terminate the string */

  if (c == SWAP || c == ASSIGN) /* deal with special commands */
    return c;
  if (c == RECENT && isvar(s)) /* call isvar() to set varid */
    return VAR;
  if (c == PEEK || c == CLEAR) {  /* these commands eat a following '\n' */
    while (isspace(cn = getch()) && cn != '\n')
      ;
    if (cn != '\n')
      ungetch(cn);
    return c;
  }

  if (isalpha(c)) {
    for (i = 0; isalpha(s[++i] = (char)(c = getch())) ;)
      ;
    s[i] = '\0';
    ungetch(c);
    if ( getmathid(s) >= 0) /* check if it is a standard math function */
      return MATH0 + math[mathid].nargs;
    else if ( isvar(s) ) /* or a variable */
      return VAR;
    else
      return -1;
  }

  if (!isdigit(c) && c != '.' && c != NEG)
    return c; /* an operator */
  i = 0;
  if (isdigit(c) || c == NEG) /* collect the integer part */
    while ( isdigit(s[++i] = (char)(c = getch())) )
      ;
  if (c == '.')
    while ( isdigit(s[++i] = (char)(c = getch())) )
      ;
  s[i] = '\0';
  if (c != EOF)
    ungetch(c);
  if (s[0] == NEG)
    s[0] = '-';
  return NUMBER;
}

