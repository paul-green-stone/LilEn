#include "../../../LilEn.h"

char g_filename[MAX_FILE_LEN];

/* ================================================================ */

cJSON* LilEn_read_json(const char* filename) {

    /* File content storage */
    char* buffer = NULL;

    /* `.json` file */
    FILE* file = NULL;
    ssize_t file_length;

    /* Parsed file content */
    cJSON* content = NULL;

    /* ================================ */

    /* In order to know what file we were trying to open, copy its name in the global buffer named `g_filename` */
    strncpy(g_filename, filename, MAX_FILE_LEN - 1);
    g_filename[MAX_FILE_LEN - 1] = '\0';

    if ((file = fopen(g_filename, "r")) == NULL) {
        return content;
    }

    /* Get the file length */
    fseek(file, 0, SEEK_END);
    file_length = ftell(file);
    rewind(file);

    /* Allocate memory for the buffer */
    if ((buffer = (char*) malloc(sizeof(char) * file_length)) == NULL) {

        fclose(file);

        return content;
    }

    /* Read a file into the buffer */
    fread(buffer, sizeof(char), file_length, file);

    fclose(file);

    content = cJSON_Parse(buffer);

    free(buffer);

    return content;
}

/* ================================================================ */

cJSON* Data_read(const char* name, const cJSON* root, cJSON_bool (check)(const cJSON* const)) {

    cJSON* data = NULL;

    return
        (root == NULL) ? 
            NULL : (name == NULL) ? 
                (cJSON*) root : (check((data = cJSON_GetObjectItemCaseSensitive(root, name)))) ? 
                    data : NULL;
}

/* ================================================================ */

#undef MAX_FILE_LEN
