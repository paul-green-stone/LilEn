#ifndef LILEN_GLOBALS_H
#define LILEN_GLOBALS_H

#include "include.h"

/* ================================================================ */

/* Recently opened file */
extern char g_filename[128];

/* A global window available everywhere */
extern Window_t g_window;

/* A global timer available everywhere */
extern Timer_t g_timer;

/* A global color available everywhere */
extern SDL_Color* g_color;

/* ================================================================ */

#endif /* LILEN_GLOBALS_H */
