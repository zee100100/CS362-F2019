CFLAGS= -Wall -fpic -coverage -lm -std=c99 -g

unittestresults: unittest1 unittest2 unittest3 unittest4 unittest5 \
	randomtestcard2 randomtestcard3 runtests
	#randomtestcard1 randomtestcard2 randomtestcard3 runtests

rngs.o: rngs.h rngs.c
	gcc -c rngs.c $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c $(CFLAGS)

unittest1: dominion.o rngs.o unittest1.c
	gcc -o unittest1 unittest1.c dominion.o rngs.o $(CFLAGS)
	#./unittest1

unittest2: dominion.o rngs.o unittest2.c
	gcc -o unittest2 unittest2.c dominion.o rngs.o $(CFLAGS)
	#./unittest2

unittest3: dominion.o rngs.o unittest3.c
	gcc -o unittest3 unittest3.c dominion.o rngs.o $(CFLAGS)
	#./unittest3

unittest4: dominion.o rngs.o unittest4.c
	gcc -o unittest4 unittest4.c dominion.o rngs.o $(CFLAGS)
	#./unittest4

unittest5: dominion.o rngs.o unittest5.c
	gcc -o unittest5 unittest5.c dominion.o rngs.o $(CFLAGS)
	#./unittest5

randomtestcard1: dominion.o rngs.o randomtestcard1.c
	gcc -o randomtestcard1 randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	#./randomtestcard1

randomtestcard2: dominion.o rngs.o randomtestcard2.c
	gcc -o randomtestcard2 randomtestcard2.c dominion.o rngs.o $(CFLAGS)
	#./randomtestcard2

randomtestcard3: dominion.o rngs.o randomtestcard3.c
	gcc -o randomtestcard3 randomtestcard3.c dominion.o rngs.o $(CFLAGS)
	#./randomtestcard3

#ifeq (0,1)
runtests: unittest1 unittest2 unittest3 unittest4 unittest5 \
	randomtestcard1 randomtestcard2 randomtestcard3
	./unittest1 > unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	./unittest2 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	./unittest3 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	./unittest4 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	./unittest5 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	#./randomtestcard1 >> randomtestresults.out
	#gcov -b -f dominion.c >> randomtestresults.out
	./randomtestcard2 >> randomtestresults.out
	gcov -b -f dominion.c >> randomtestresults.out
	./randomtestcard3 >> randomtestresults.out
	gcov -b -f dominion.c >> randomtestresults.out
#endif

clean:
	rm -f *.o unittest1 unittest2 unittest3 unittest4 unittest5 \
	randomtestcard1 randomtestcard2 randomtestcard3 *.gcov *.gcda *.gcno *.out
