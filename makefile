rational_math: rational.o test_rational.o
	gcc -g -Wall test_rational.o rational.o -lm -o rational_math 

rational.o: rational.h rational.c
	gcc -g -Wall -c rational.c

test_rational.o: rational.h test_rational.c
	gcc -g -Wall -c test_rational.c

clean:
	rm -f rational.o test_rational.o rational_math

all: rational_math