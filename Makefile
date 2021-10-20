CC    	  = gcc
CFLAGS	  = -Wall

SRCS 	  = $(wildcard src/*.c)
OBJS 	  = $(SRCS:.c=.o)

TEST_SRCS = $(wildcard test/*.c)
TESTS     = $(TEST_SRCS:.c=.exe)

run: regparser
	./regparser

regparser: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

test/test_%.exe: test/test_%.c $(filter-out src/main.c, $(SRCS))
	$(CC) $(CFLAGS) -o $@ $^

test: $(TESTS)
	@for i in $^; do echo -n $$i; ./$$i || exit 1; echo "  ...passed";done

clean:
	rm -f ./regparser ./src/*.o ./test/*.exe

.PHONY: run test clean
