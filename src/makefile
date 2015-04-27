IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=../obj

LIBS=-lm -lpthread

_DEPS = http.h config.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = server.o http.o config.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

server: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
