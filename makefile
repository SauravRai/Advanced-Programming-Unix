OUTPUT:myStat.o errno.o
	cc -o OUTPUT myStat.o errno.o -lm
myStat.o: apue.h
errno.o: apue.h
clean:
	rm *.o


