CFLAGS = -g -Wall -O3

all: tester

tester: tester.o tokenizer.o
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o tester
