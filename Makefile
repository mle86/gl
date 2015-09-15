CC=gcc
CFLAGS=-O2 -std=c99 -Wall -Wextra -pedantic

BIN=gl
BINDEST=/usr/local/bin/

MAN=gl.1
MANDEST=/usr/local/share/man/man1/


all: $(BIN)

$(BIN): gl.o aux.o group.o

install: $(BIN)
	strip $(BIN)
	cp $(BIN) $(BINDEST)
	
	mkdir -p $(MANDEST)
	cp $(MAN) $(MANDEST)
	gzip -f $(MANDEST)/$(MAN)

clean:
	rm -f $(BIN) *.o *~ *.bak
