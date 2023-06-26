CC=gcc
cflags= -Wall -lm
out=lab2
outbroker=broker
outworker=worker

all:
	$(CC) broker.c -o $(outbroker)
	$(CC) worker.c -o $(outworker)
	$(CC) lab2.c -o $(out) $(cflags)
clean:
	rm $(out)
fullclean:
	rm -f $(out) $(outbroker) $(outworker)