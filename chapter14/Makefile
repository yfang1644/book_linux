CC      = arm-linux-gcc
SRC     = graphics.c line.c ellipse.c rectangle.c

LIBNAME = graphics
VERSION = 0
MINOR   = 0

all: lib$(LIBNAME).so lib$(LIBNAME).so.$(VERSION) mosaic main

lib$(LIBNAME).so: lib$(LIBNAME).so.$(VERSION).$(MINOR)
	ln -sf $^ $@

lib$(LIBNAME).so.$(MINOR): lib$(LIBNAME).so.$(VERSION).$(MINOR)
	ln -sf $^ $@

lib$(LIBNAME).so.$(VERSION).$(MINOR): $(SRC)
	$(CC) -o $@ $^ -shared -fPIC -Wl,-soname,lib$(LIBNAME).so.$(VERSION) -lm

mosaic: mosaic.c  lib$(LIBNAME).so
	$(CC) -o $@ $< -L. -l$(LIBNAME) -pthread

main: main.c  lib$(LIBNAME).so
	$(CC) -o $@ $< -L. -l$(LIBNAME)

clean:
	$(RM) lib$(LIBNAME).* mosaic main
