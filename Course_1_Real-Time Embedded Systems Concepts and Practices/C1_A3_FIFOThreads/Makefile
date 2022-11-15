INCLUDE_DIRS = 
LIB_DIRS = 
CC=gcc

CDEFS=
CFLAGS= -O0 -Wall -g -D_GNU_SOURCE $(INCLUDE_DIRS) $(CDEFS)
LIBS= 

HFILES= 
CFILES= fifothreads.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	fifothreads

clean:
	-rm -f *.o *.d
	-rm -f fifothreads

fifothreads: fifothreads.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $@.o -lpthread

depend:

.c.o:
	$(CC) $(CFLAGS) -c $<