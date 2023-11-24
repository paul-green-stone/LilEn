#ifndef LILEN_FILE_H
#define LILEN_FILE_H

#include "../../LilEn.h"

/* ================================================================ */

/**
 * The function tries to read a `.json` file into a dynamically allocated buffer.
 * After the reading is complete, it parses the content of the buffer creating a `cJSON` struct.
 * 
 * @return Returns a pointer to a parsed `cJSON` struct on success or NULL on failure; call `LilEn_print_error()` for more information.
*/
extern cJSON* LilEn_read_json(const char* filename);

/* ================================================================ */

#endif /* LILEN_FILE_H */