CC := gcc

CFLAGS := -g
ALL_CFLAGS := -Wall -Wextra -pedantic-errors -O2

LDFLAGS := -lSDL2 -lSDL2_image -lm ../../liblilen.a 

PROG := a.out

# ================================================================ #

# Make a window.o object file
$(PROG): main.c
	$(CC) $(ALL_CFLAGS) $(CFLAGS) -o $@ $< $(LDFLAGS)

# ================================ #

.PHONY: clean

clean:
	rm -rf $(OBJDIR) ./*.a ./*.o ./*.out