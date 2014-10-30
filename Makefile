# debugging
CC = gcc -O0 -Wall -Wunused -Wextra -g
LM = -lm
# optimized compiling
CX = icc -O2 -ipo -Wall -Wunused -Wremarks -Wcheck -wd11001 -wd11006
LMX =

deps = Makefile
srcs = $(wildcard ex*-*.c)
bins = $(patsubst %.c,%, $(srcs))
bins_d = $(patsubst %.c,%_d, $(srcs))

all: $(bins)

$(bins) : %: %.c $(deps)
	$(CX) -o $@ $< $(LMX)

$(bins_d) : %_d: %.c $(deps)
	$(CC) -o $@ $< $(LM)

clean:
	rm -rf $(bins) $(bins_d) *~ a.out bin obj r[0-9][0-9][0-9][a-z]*
	rstrip.py -Rlv

