CC=gcc
CFLAGS=-Wall -O3
LDFLAGS=-pthread
COMPILEONLY=-c
SOURCES=parallel_primes.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=$(firstword $(SOURCES:.c=))

.PHONY: clean run
.SUFFIXES:
.SUFFIXES: .c .o

all: $(SOURCES) $(EXECUTABLE)

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

build: clean all

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(COMPILEONLY) $< -o $@
