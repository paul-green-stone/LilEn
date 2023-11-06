#ifndef LILEN_ERROR_H
#define LILEN_ERROR_H

#include "../../LilEn.h"

/* ================================================================ */

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

// enum ErrorCodes {

// };

/**
 * Return an error message string related to LilEn.
*/
extern char* LilEn_get_error(int error);

/* ================================ */

/**
 * Print information about the last error occured.
*/
extern void LilEn_print_error(void);

/* ================================================================ */

#endif