#include "../include.h"

/* ================================================================ */
/* ============================ STATIC ============================ */
/* ================================================================ */

static int LilEn_lookup_SDL(const char* flag) {

    static const struct {
        const char *str;
        int value;
    } sdl_flags[] = {
        {"SDL_INIT_TIMER", SDL_INIT_TIMER},
        {"SDL_INIT_AUDIO", SDL_INIT_AUDIO},
        {"SDL_INIT_VIDEO", SDL_INIT_VIDEO},
        {"SDL_INIT_JOYSTICK", SDL_INIT_JOYSTICK},
        {"SDL_INIT_HAPTIC", SDL_INIT_HAPTIC},
        {"SDL_INIT_GAMECONTROLLER", SDL_INIT_GAMECONTROLLER},
        {"SDL_INIT_EVENTS", SDL_INIT_EVENTS},
        {"SDL_INIT_EVERYTHING", SDL_INIT_EVERYTHING},
    };

    size_t i = 0;
    size_t array_size = sizeof(sdl_flags) / sizeof(sdl_flags[0]);

    for (; i < array_size; i++) {

        if (strcmp(flag, sdl_flags[i].str) == 0) {
            return sdl_flags[i].value;
        }
    }

    return -1;
}

/* ================================================================ */

static int LilEn_lookup_SDL_image(const char* flag) {

    static const struct {
        const char *str;
        int value;
    } sdl_flags[] = {
        {"IMG_INIT_JPG", IMG_INIT_JPG},
        {"IMG_INIT_PNG", IMG_INIT_PNG},
        {"IMG_INIT_TIF", IMG_INIT_TIF},
        {"IMG_INIT_WEBP", IMG_INIT_WEBP},
        {"IMG_INIT_JXL", IMG_INIT_JXL},
        {"IMG_INIT_AVIF", IMG_INIT_AVIF},
    };

    size_t i = 0;
    size_t array_size = sizeof(sdl_flags) / sizeof(sdl_flags[0]);

    for (; i < array_size; i++) {

        if (strcmp(flag, sdl_flags[i].str) == 0) {
            return sdl_flags[i].value;
        }
    }

    return -1;
}

/* ================================================================ */
/* ============================ EXTERN ============================ */
/* ================================================================ */

char* LilEn_read_data_file(const char* filename) {

    FILE* input = NULL;
    char* buffer = NULL;
    ssize_t file_size;

    if ((input = fopen(filename, "r")) == NULL) {

        /* Implement a propper error handling mechanism */

        return buffer;
    }

    /* Get the file size */
    fseek(input, 0, SEEK_END);
    file_size = ftell(input);
    rewind(input);

    /* Allocate memory for the buffer */
    if ((buffer = (char*) mallo     c(sizeof(char) * file_size)) == NULL) {

        /* Implement a propper error handling mechanism */

        fclose(input);

        return buffer;
    }

    /* Read the file into the buffer */
    fread(buffer, sizeof(char), file_size, input);

    fclose(input);

    return buffer;
}

/* ================================================================ */

extern int LilEn_init(void) {

    /* core.json file content */
    char* core_input = NULL;
    /* Parsed .json */
    cJSON* core_root_json = NULL;
    
    size_t array_size;
    size_t i = 0;

    /* ================================================================ */
    /* =========== Retrieving SDL flags from the core file ============ */
    /* ================================================================ */

    /* Flags retrieved from a .json file */
    cJSON* c_flags = NULL;
    /* Their corresponding integer values */
    uint32_t flags = 0;

    {
        /* Read data from a file */
        if ((core_input = LilEn_read_data_file("../../data/core/core.json")) == NULL) {

            /* Implement a propper error handling mechanism */

            return EXIT_FAILURE;
        }

        /* Parse the data .json file */
        if ((core_root_json = cJSON_Parse(core_input)) == NULL) {

            /* Implement a propper error handling mechanism */

            free(core_input);

            return EXIT_FAILURE;
        }

        if ((c_flags = cJSON_GetObjectItemCaseSensitive(core_root_json, "SDL2")) == NULL) {

            /* Implement a propper error handling mechanism */

            free(core_input);

            return EXIT_FAILURE;
        }

        if (!cJSON_IsArray(c_flags)) {

            /* Implement a propper error handling mechanism */

            free(core_input);

            return EXIT_FAILURE;
        }

        array_size = (size_t) cJSON_GetArraySize(c_flags);

        for (; i < array_size; i++) {

            int flag = 0;

            cJSON* item = cJSON_GetArrayItem(c_flags, i);

            if ((flag = LilEn_lookup_SDL(item->valuestring)) == -1) {
                continue ;
            }

            flags |= flag;
        }
    }

    /* ================================================================ */
    /* ================= Initializing a SDL2 Library ================== */
    /* ================================================================ */

    if (SDL_Init(flags) != 0) {

        /* Implement a propper error handling mechanism */

        free(core_input);

        return EXIT_FAILURE;
    }

    /* ================================================================ */
    /* ======== Retrieving SDL_image flags from the core file ========= */
    /* ================================================================ */

    {
        /* Read data from a file */
        if ((core_input = LilEn_read_data_file("../../data/core/core.json")) == NULL) {

            /* Implement a propper error handling mechanism */

            return EXIT_FAILURE;
        }

        /* Parse the data .json file */
        if ((core_root_json = cJSON_Parse(core_input)) == NULL) {

            /* Implement a propper error handling mechanism */

            free(core_input);

            return EXIT_FAILURE;
        }

        if ((c_flags = cJSON_GetObjectItemCaseSensitive(core_root_json, "SDL_image")) == NULL) {

            /* Implement a propper error handling mechanism */

            free(core_input);

            return EXIT_FAILURE;
        }

        if (!cJSON_IsArray(c_flags)) {

            /* Implement a propper error handling mechanism */

            free(core_input);

            return EXIT_FAILURE;
        }

        array_size = (size_t) cJSON_GetArraySize(c_flags);

        for (; i < array_size; i++) {

            int flag = 0;

            cJSON* item = cJSON_GetArrayItem(c_flags, i);

            if ((flag = LilEn_lookup_SDL_image(item->valuestring)) == -1) {
                continue ;
            }

            flags |= flag;
        }
    }

    /* ================================================================ */
    /* =============== Initializing a SDL_image Library =============== */
    /* ================================================================ */

    if (!(IMG_Init(flags) & flags)) {

        /* Implement a propper error handling mechanism */

        free(core_input);

        return EXIT_FAILURE;
    }

    cJSON_Delete(core_root_json);
    free(core_input);

    return EXIT_SUCCESS;
}

/* ================================================================ */

void LilEn_quit(void) {

    IMG_Quit();
    SDL_Quit();

    return ;
}
