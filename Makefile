CC=gcc
CFLAGS=-O2 -I. -Wall
BIN=gl
DEST=/usr/local/bin/gl
CHOWN=root:root
SRC=gl.c

MAN=gl.1
MANDEST=/usr/local/share/man/man1/


default:
	$(CC) $(CFLAGS) -o $(BIN) -DPROGNAME='"$(BIN)"' $(SRC)

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
	rm -f $(BIN) *.so *.o *.a *~ *.bak
