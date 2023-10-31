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

/* ================================================================ */

void Window_clear(const Window_t w) {

    SDL_RenderClear((w == NULL) ? g_window->renderer : w->renderer);

    return ;
}

/* ================================================================ */

void Window_update(const Window_t w) {

    SDL_RenderPresent((w == NULL) ? g_window->renderer : w->renderer);

    return ;
}

/* ================================================================ */

void Window_display_grid(const Window_t w, int cell) {

    Window_t target = (w == NULL) ? g_window : w;

    size_t rows = 0;
    size_t columns = 0;

    int width = 0;
    int height = 0;

    size_t i = 0;

    /* ================================ */

    SDL_GetWindowSize(target->window, &width, &height);

    rows = height / cell;
    columns = width / cell;

    /* Drawing columns */
    for (; i < columns; i++) {
        SDL_RenderDrawLine(target->renderer, i * cell, 0, i * cell, height);
    }

    /* Drawing rows */
    for (i = 0; i < rows; i++) {
        SDL_RenderDrawLine(target->renderer, 0, i * cell, width, i * cell);
    } 

    return ;
}
