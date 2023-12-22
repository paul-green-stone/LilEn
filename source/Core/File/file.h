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

/**
 * The function extracts a piece of information named `data_name` from a parsed `root` `cJSON*` object.
 * `check` is a function pointer that is used to check if desired data belongs to the type.
 * 
 * @return Extracted data on success or `root` itself if `name` is NULL. On error NULL is returned.
*/
extern cJSON* Data_read(const char* data_name, const cJSON* root, cJSON_bool (check)(const cJSON* const));

/* ================================================================ */

#endif /* LILEN_FILE_H */
