CC=clang
CFLAGS= -g 
SRCDIR= ./src
INCLUDEDIR= -I ./include -I.
LIBS= -lcurses

PROGRAMS=demo-2048-c \

ALL: $(PROGRAMS)
demo-2048-c: $(SRCDIR)/demo2048c.c $(SRCDIR)/main.c
	$(CC) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS) 

.PHONY: clean
clean: 
	rm  $(PROGRAMS)
