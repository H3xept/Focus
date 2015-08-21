CC=gcc
CFLAGS=-Wall -g

clean:
	rm -f focus
	rm -f focus.o
all: focus

focus: focus.o bstrlib.o db.o