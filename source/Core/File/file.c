#include "../../LilEn.h"

char g_filename[MAX_FILE_LEN];

/* ================================================================ */

cJSON* LilEn_read_json(const char* filename) {

    char* buffer = NULL;

    FILE* input_file = NULL;
    ssize_t file_length;

    cJSON* content = NULL;

    strncpy(g_filename, filename, MAX_FILE_LEN - 1);
    g_filename[MAX_FILE_LEN - 1] = '\0';

    if ((input_file = fopen(g_filename, "r")) == NULL) {
        return content;
    }

    /* Get the file length */
    fseek(input_file, 0, SEEK_END);
    file_length = ftell(input_file);
    rewind(input_file);

    /* Allocate memory for the buffer */
    if ((buffer = (char*) malloc(sizeof(char) * file_length)) == NULL) {

        fclose(input_file);

        return content;
    }

    /* Read a file into a buffer */
    fread(buffer, sizeof(char), file_length, input_file);

    fclose(input_file);

    content = cJSON_Parse(buffer);

    free(buffer);

    return content;
}

/* ================================================================ */

#undef MAX_FILE_LEN
