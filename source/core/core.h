#ifndef LILEN_CORE_H
#define LILEN_CORE_H

#include "../include.h"

/* ================================================================ */

/**
 * Start up the engine routine. The function initializes SDL2, SDL_image library and a standard random number generator.
 * It also initializes some of the global variables. Use `core.json` to specify flags to be initialized.
*/
extern int LilEn_init(void);

/* ================================ */

/**
 * 
*/
extern void LilEn_quit(void);

/* ================================ */

/**
 * Read the data file. The function opens a file, allocates enough space to store its data and read the content into the allocated buffer. It's a user's sole responsibility to free a buffer after its usage.
*/
extern char* LilEn_read_data_file(const char* filename);

/* ================================================================ */

#endif /* LILEN_CORE_H */