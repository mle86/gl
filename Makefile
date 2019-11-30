CC=gcc
CFLAGS=-O2 -std=c99 -Wall -Wextra -pedantic
LD=gcc
LDFLAGS=$(CFLAGS)

BIN=gl
BINDEST=/usr/local/bin/

MAN=gl.1
MANDEST=/usr/local/share/man/man1/


all: $(BIN)

README.md: man/gl.1 man/*.md
	git submodule update --init man/man-to-md/
	perl man/man-to-md.pl --word gl \
		--paste-section-after 'EXAMPLE:Installation.md' \
		--paste-section-after 'EXAMPLE:Standards and Dependencies.md' \
		<$< >$@

$(BIN): src/gl.o src/aux.o src/group.o
	$(LD) $(LDFLAGS) -o $@ $^

install: $(BIN)
	strip $(BIN)
	cp $(BIN) $(BINDEST)
	
	mkdir -p $(MANDEST)
	cp man/$(MAN) $(MANDEST)
	gzip -f $(MANDEST)/$(MAN)

clean:
	rm -f $(BIN) src/*.o src/*~ src/*.bak
