INCLUDE_DIRS = 
LIB_DIRS = 
CC=gcc

CDEFS=
CFLAGS= -O0 -Wall -g -D_GNU_SOURCE $(INCLUDE_DIRS) $(CDEFS)
LIBS= 

HFILES= 
CFILES= thread_affinity.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	thread_affinity

clean:
	-rm -f *.o *.d
	-rm -f thread_affinity

thread_affinity: thread_affinity.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $@.o -lpthread

depend:

.c.o:
	$(CC) $(CFLAGS) -c $<