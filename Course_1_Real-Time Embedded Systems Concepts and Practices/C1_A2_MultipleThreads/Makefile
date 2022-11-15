INCLUDE_DIRS = 
LIB_DIRS = 
CC=gcc

CDEFS=
CFLAGS= -O0 -Wall -g $(INCLUDE_DIRS) $(CDEFS)
LIBS= 

HFILES= 
CFILES= multiplethreads.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	multiplethreads

clean:
	-rm -f *.o *.d
	-rm -f multiplethreads

multiplethreads: multiplethreads.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $@.o -lpthread

depend:

.c.o:
	$(CC) $(CFLAGS) -c $<