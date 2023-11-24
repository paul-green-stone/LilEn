OBJDIR		:= objects
OBJS 		:= $(addprefix $(OBJDIR)/, Window.o Core.o Timer.o)
COREOBJS	:= $(addprefix $(OBJDIR)/, core.o cJSON.o error.o file.o)

INCLUDE		:= source/LilEn.h
WINDOW		:= $(addprefix source/Window/, window.c window.h)
TIMER		:= $(addprefix source/Timer/, timer.c timer.h)
CORE		:= $(addprefix source/Core/, core.c core.h)
CJSON		:= $(addprefix source/Core/cJSON/, cJSON.c cJSON.h)
ERROR		:= $(addprefix source/Core/Error/, error.c error.h)
FILE		:= $(addprefix source/Core/File/, file.c file.h)

LIBRARY 	:= liblilen.a
SHARED		:= liblilen.so

AR 			:= ar
ARFLAGS 	:= -r -c

LD			:= ld
LDFLAGS 	:= `pkg-config --libs SDL2_image` `pkg-config --cflags SDL2_image` `pkg-config --libs sdl2` `pkg-config --cflags sdl2` -lm

CC			:= gcc
CFLAGS 		:= -g -c `pkg-config --libs SDL2_image` `pkg-config --cflags SDL2_image` `pkg-config --libs sdl2` `pkg-config --cflags sdl2` -lm
ALL_CFLAGS 	:= -Wall -Wextra -pedantic-errors -fPIC -O2

PREFIX		:= /usr/local
INCLUDEDIR 	:= $(PREFIX)/include
LIBDIR		:= $(PREFIX)/lib

# ================================================================ #

all: $(LIBRARY)

$(LIBRARY): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(OBJDIR)/Window.o: $(WINDOW) $(INCLUDE)
	$(CC) $(ALL_CFLAGS) $(CFLAGS) -o $@ $<

$(OBJDIR)/Timer.o: $(TIMER) $(INCLUDE)
	$(CC) $(ALL_CFLAGS) $(CFLAGS) -o $@ $<

$(OBJDIR)/Core.o: $(COREOBJS)
	$(LD) -r -o $@ $^
	rm $(COREOBJS)

$(OBJDIR)/core.o: $(CORE) $(INCLUDE)
	$(CC) $(ALL_CFLAGS) $(CFLAGS) -o $@ $<

$(OBJDIR)/file.o: $(FILE) $(INCLUDE)
	$(CC) $(ALL_CFLAGS) $(CFLAGS) -o $@ $<

$(OBJDIR)/error.o: $(ERROR) $(INCLUDE)
	$(CC) $(ALL_CFLAGS) $(CFLAGS) -o $@ $<

$(OBJDIR)/cJSON.o: $(CJSON) $(INCLUDE)
	$(CC) $(ALL_CFLAGS) $(CFLAGS) -o $@ $<

install:
	$(CC) -shared -o $(SHARED) $(OBJDIR)/*.o
	mkdir -p $(INCLUDEDIR)/LilEn
	cp ./source/*.h $(INCLUDEDIR)/LilEn
	cp -rf ./source/*/ $(INCLUDEDIR)/LilEn
	mv $(SHARED) $(LIBDIR)

uninstall:
	rm -rf $(INCLUDEDIR)/LilEn

$(shell mkdir -p $(OBJDIR))

# ================================ #

.PHONY: clean

clean:
	rm -rf $(OBJDIR) $(LIBRARY)