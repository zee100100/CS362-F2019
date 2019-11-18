testme: testme.c
	gcc -o testme -coverage testme.c

runtests: testme
	./testme
	gcov testme.c

clean:
	rm -f *.o testme *.gcov *.gcda *.gcno
