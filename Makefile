CC=g++
CFLAGS=-I.
DEPS = run.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

run: run.o obj.o 
	$(CC) -o run run.o obj.o -I.

clean:
	rm -rf run run.o obj.o