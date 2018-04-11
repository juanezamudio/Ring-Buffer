#
# Simple Makefile to build the ringbuffer program
#
# Rett Bull
# Pomona College
# May 16, 2017
#
CC = gcc
CFLAGS = -O -Wall -Werror
LIBS = -lpthread

all: ringbuf

ringbuf: ringbuf.c
	$(CC) $(CFLAGS) -o ringbuf ringbuf.c $(LIBS) 

clean:
	rm -rf ringbuf
