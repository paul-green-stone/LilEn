#ifndef LILEN_CORE_H
#define LILEN_CORE_H

#include "../LilEn.h"

/* ================================================================ */

/**
 * Draw a rectangle on the screen. Always use the global window
*/
#define draw_rect(r) (LilEn_draw_rect(g_window, r))

/**
 * Start up the engine routine. The function initializes SDL2, SDL_image library and a standard random number generator.
 * It also initializes some of the global variables. Use `core.json` to specify flags to be initialized.
*/
extern int LilEn_init(const char* filename);

/* ================================ */

/**
 * Quit the engine. Deallocate resources associated with it.
*/
extern void LilEn_quit(void);

/* ================================ */

/**
 * Read the data file. The function opens a file, allocates enough space to store its data and read the content into the allocated buffer. It's a user's sole responsibility to free a buffer after its usage.
*/
extern char* LilEn_read_data_file(const char* filename);

/* ================================ */

/**
 * Outputs the FPS to the console.
*/
extern void LilEn_log_FPS(void);

/* ================================ */

/**
 * 
*/
extern void LilEn_set_colorRGB(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

/* ================================ */

extern void LilEn_set_colorHEX(uint32_t c);

/* ================================ */

/**
 * Draw a rectangle in the screen.
*/
extern void LilEn_draw_rect(const Window_t w, const SDL_Rect* r);

/* ================================================================ */

#endif /* LILEN_CORE_H */