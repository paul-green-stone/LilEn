#include "../LilEn.h"

#define DEFAULT_SETTINGS "../../config/core.json"

Timer_t g_timer = NULL;

SDL_Color* g_color = NULL;

/**
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
*/

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

/**
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
*/

/* ================================================================ */
/* ============================ EXTERN ============================ */
/* ================================================================ */


extern int LilEn_init(const char* filename) {

    /* Parsed .json */
    cJSON* root = NULL;
    
    size_t array_size;
    size_t i = 0;

    /* Data retrieved from a parsed .json file */
    cJSON* json_data = NULL;

    /* Initialization flags */
    int flags = 0;

    /* ================================================================ */

    if ((g_color = (SDL_Color*) calloc(1, sizeof(SDL_Color))) == NULL) {
        goto CLEANUP;
    }

    /* ================================================================ */

    if ((g_timer = Timer_new()) == NULL) {
        goto CLEANUP;
    }

    /* ================================================================ */
    /* =========== Retrieving SDL flags from the core file ============ */
    /* ================================================================ */

    {
        /* Read data from a file */
        if ((root = LilEn_read_json(filename == NULL ? DEFAULT_SETTINGS : filename)) == NULL) {
            goto CLEANUP;
        }

        if ((json_data = cJSON_GetObjectItemCaseSensitive(root, "SDL2")) == NULL) {
            goto CLEANUP;
        }

        if (!cJSON_IsArray(json_data)) {
            goto CLEANUP;
        }

        array_size = (size_t) cJSON_GetArraySize(json_data);

        for (; i < array_size; i++) {

            int flag = 0;

            cJSON* item = cJSON_GetArrayItem(json_data, i);

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
        goto CLEANUP;
    }

    /* ================================================================ */
    /* ======== Retrieving SDL_image flags from the core file ========= */
    /* ================================================================ */

    flags = 0;

    {
        if ((json_data = cJSON_GetObjectItemCaseSensitive(root, "SDL_image")) == NULL) {
            goto CLEANUP;
        }

        if (!cJSON_IsArray(json_data)) {
            goto CLEANUP;
        }

        array_size = (size_t) cJSON_GetArraySize(json_data);

        for (i = 0; i < array_size; i++) {

            int flag = 0;

            cJSON* item = cJSON_GetArrayItem(json_data, i);

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
        goto CLEANUP;
    }

    /* ================================================================ */

    if ((json_data = cJSON_GetObjectItemCaseSensitive(root, "FPS")) == NULL) {
        Timer_set(g_timer, 1.0f / 60);
    }

    Timer_set(g_timer, 1.0f / json_data->valueint);

    /* ================================================================ */

    /* Initializing a random number generator */
    srand((unsigned) time(0));

    cJSON_Delete(root);

    return EXIT_SUCCESS;

    /* ================================================================ */
    /* ====================== Handling an error ======================= */
    /* ================================================================ */

    CLEANUP:

        if (root != NULL) {
            cJSON_Delete(root);
        }

        LilEn_quit();

        return EXIT_FAILURE;
}

/* ================================================================ */

void LilEn_quit(void) {

    Timer_destroy(&g_timer);
    Window_destroy(&g_window);

    free(g_color);

    IMG_Quit();
    SDL_Quit();

    return ;
}

/* ================================================================ */

void LilEn_log_FPS(void) {

    if (g_timer != NULL) {
        printf("FPS: %.2f\n", 1.0f / g_timer->acc);
    }

    return ;
}

/* ================================================================ */

void LilEn_set_colorRGB(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {

    *g_color = (SDL_Color) {r, g, b, a};

    SDL_SetRenderDrawColor(g_window->renderer, g_color->r, g_color->g, g_color->b, g_color->a);

    return ;
}

/* ================================================================ */

void LilEn_set_colorHEX(uint32_t c) {
    
    *g_color = (SDL_Color) {(c >> 16) & 0xFF, (c >> 8) & 0xFF, c & 0xFF, 0xFF};

    SDL_SetRenderDrawColor(g_window->renderer, g_color->r, g_color->g, g_color->b, g_color->a);

    return ;
}

/* ================================================================ */

void LilEn_draw_rect(const Window_t w, const SDL_Rect* r) {

    if (r == NULL) {
        return ;
    }

    if ((w == NULL) && (g_window) == NULL) {

        /* Implement a mechanism to handle this situation */

        return ;
    }   

    SDL_RenderFillRect((w == NULL) ? g_window->renderer : w->renderer, r);

    return ;
}

/* ================================================================ */

#undef DEFAULT_SETTINGS
