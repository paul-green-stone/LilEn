CC := gcc

CFLAGS := -g
ALL_CFLAGS := -Wall -Wextra -pedantic-errors -O2

LDFLAGS := `pkg-config --libs SDL2_image` `pkg-config --cflags SDL2_image` `pkg-config --libs sdl2` `pkg-config --cflags sdl2` -lm ../../liblilen.a 

PROG := a.out

# ================================================================ #

# Make a window.o object file
$(PROG): main.c
	$(CC) $(ALL_CFLAGS) $(CFLAGS) -o $@ $< $(LDFLAGS)

# ================================ #

.PHONY: clean

clean:
	rm -rf $(OBJDIR) ./*.a ./*.o ./*.out