CC=gcc
CFLAGS=-O2 -I. -Wall
BIN=gl
DEST=/usr/local/bin/$(BIN)
CHOWN=root:root

MAN=gl.1
MANDEST=/usr/local/share/man/man1/


default: $(BIN)

$(BIN): gl.o aux.o group.o

install:
	strip $(BIN)
	cp $(BIN) $(DEST)
	chown $(CHOWN) $(DEST)
	
	mkdir -p $(MANDEST)
	cp $(MAN) $(MANDEST)
	chown $(CHOWN) $(MAN)
	chmod 0644 $(MAN)

complete: clean default install

clean:
	rm -f $(BIN) *.o *~ *.bak
