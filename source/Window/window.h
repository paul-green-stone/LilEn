#ifndef LILEN_WINDOW_H
#define LILEN_WINDOW_H

#include "../include.h"

/* ================================================================ */

struct window {

    SDL_Window* window;

    SDL_Renderer* renderer;
};

typedef struct window Window;

typedef Window* Window_t;

/* ================================================================ */
/* ========================== INTERFACE =========================== */
/* ================================================================ */

/**
 * Dynamically allocate a new instance of a `Window_t` type.
*/
extern Window_t Window_new(const char* title, int w, int h, uint32_t w_flags, uint32_t r_flags);

/* ================================ */

/**
 * Destroy a window `w` of type `Window_t` and data associated with it. Deallocate memory occupied by a window `w`.
*/
extern int Window_destroy(Window_t* w);

/* ================================ */

/**
 * Fill the entire screen with color.
*/
extern void Window_clear(const Window_t w);

/* ================================ */

/**
 * Update a window.
*/
extern void Window_update(const Window_t w);

/* ================================ */

/**
 * Display a grid with the cell of size `cell`.
*/
extern void Window_display_grid(const Window_t w, int cell);

/* ================================================================ */

#endif /* LILEN_WINDOW_H */
