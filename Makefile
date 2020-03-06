CC=g++
CFLAGS=-I.
DEPS = run.h
OBJS = run.o obj.o
TARGET=run

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS)

clean:
	rm -rf $(TARGET) $(OBJS)