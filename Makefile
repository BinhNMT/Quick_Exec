CC=gcc
run: run.c
	$(CC) -o run run.c
clean:
	rm -rf run