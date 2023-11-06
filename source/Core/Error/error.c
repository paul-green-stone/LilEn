#include "../../LilEn.h"

#define BUFFER 1024

/* ================================================================ */

void LilEn_print_error(void) {

    /* ======================== Standard error ======================== */

    char error_msg[BUFFER];

    strncpy(error_msg, (char*) strerror(errno), BUFFER - 1);

    if (error_msg[0] != '\0') {

        switch (errno) {

            case ENOENT:
                sprintf(error_msg, "Error opening a file %s: %s%s%s", g_filename, ANSI_COLOR_RED, (char*) strerror(errno), ANSI_COLOR_RESET);

                break ;
        }

        fprintf(stderr, "%s\n", error_msg);

        return ;
    }

    /* ========================== SDL2 error ========================== */

    strncpy(error_msg, (char*) SDL_GetError(), BUFFER - 1);

    if (error_msg[0] != '\0') {

        fprintf(stderr, "%serror%s: %s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET, error_msg);

        return ;
    }

    /* ======================= SDL_image error ======================== */

    strncpy(error_msg, (char*) IMG_GetError(), BUFFER - 1);

    if (error_msg[0] != '\0') {

        fprintf(stderr, "%serror%s: %s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET, error_msg);

        return ;
    }

    /* ========================= cJSON error ========================== */

    strncpy(error_msg, (char*) cJSON_GetErrorPtr(), BUFFER - 1);

    if (error_msg[0] != '\0') {

        fprintf(stderr, "%serror%s: %s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET, error_msg);

        return ;
    }

    return ;
}