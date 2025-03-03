all: rtclock.o parOdds.h parOdds.c seqOdds.c
	gcc -Wall -g -o parOdds parOdds.c rtclock.o -lpthread
	gcc -Wall -g -o seqOdds seqOdds.c rtclock.o

rtclock.o: rtclock.h rtclock.c
	gcc -Wall -g -c rtclock.c

clean:
	rm -rf *.o parOdds seqOdds
