#ifndef LILEN_GLOBALS_H
#define LILEN_GLOBALS_H

#include "LilEn.h"

#define MAX_FILE_LEN 128

/* ================================================================ */

/* Recently opened file */
extern char g_filename[MAX_FILE_LEN];

/* A global window available everywhere */
extern Window_t g_window;

/* A global timer available everywhere */
extern Timer_t g_timer;

/* A global color available everywhere */
extern SDL_Color* g_color;

/* ================================================================ */

#endif /* LILEN_GLOBALS_H */
