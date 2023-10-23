#include "../include.h"

Window_t g_window = NULL;

/* ================================================================ */

Window_t Window_new(const char* title, int w, int h, uint32_t w_flags, uint32_t r_flags) {

    Window_t window = NULL;

    if ((window = (Window_t) malloc(sizeof(Window))) == NULL) {

        /* Implement a propper error handling mechanism */
        
        return window;
    }

    /* ================================ */

    if ((window->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, w_flags)) == NULL) {

        /* Implement a propper error handling mechanism */

        Window_destroy(&window);

        return window;
    }

    if ((window->renderer = SDL_CreateRenderer(window->window, -1, r_flags)) == NULL) {

        /* Implement a propper error handling mechanism */

        Window_destroy(&window);

        return window;
    }

    /* ================================ */  

    g_window = (g_window) ? g_window : window;

    return window;
}

/* ================================================================ */

int Window_destroy(Window_t* w) {
    
    if ((w == NULL) || (*w == NULL)) {

        /* Implement a propper error handling mechanism */

        return EXIT_FAILURE;
    }

    SDL_DestroyRenderer((*w)->renderer);

    SDL_DestroyWindow((*w)->window);

    free(*w);

    *w = NULL;

    return EXIT_SUCCESS;
}
