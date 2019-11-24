CFLAGS= -Wall -fpic -coverage -lm -std=c99

unittestresults: randomtestcard1 randomtestcard2 randomtestcard3 runtests

rngs.o: rngs.h rngs.c
	gcc -c rngs.c $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c $(CFLAGS)

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
runtests: randomtestcard1 randomtestcard2 randomtestcard3
	./randomtestcard1 > randomtestresults.out
	gcov -b -f dominion.c >> randomtestresults.out
	./randomtestcard2 >> randomtestresults.out
	gcov -b -f dominion.c >> randomtestresults.out
	./randomtestcard3 >> randomtestresults.out
	gcov -b -f dominion.c >> randomtestresults.out
#endif

clean:
	rm -f *.o randomtestcard1 randomtestcard2 randomtestcard3 *.gcov *.gcda *.gcno *.out
