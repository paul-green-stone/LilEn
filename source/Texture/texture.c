#include "../LilEn.h"

/* ================================================================ */

Texture_t Texture_new(const char* pathname, const Window_t w) {

    Texture_t t = NULL;
    SDL_Surface* s = NULL;

    if ((w == NULL) || (g_window == NULL)) {

        /* Set an error code */
        return t;
    }

    if ((t = calloc(1, sizeof(Texture))) == NULL) {
        return t;
    }

    if ((s = IMG_Load(pathname)) == NULL) {
        Texture_destroy(&t);

        return t;
    }

    if ((t->t = SDL_CreateTextureFromSurface((w != NULL) ? w->renderer : g_window->renderer, s)) == NULL) {

        SDL_FreeSurface(s);

        Texture_destroy(&t);

        return t;
    }

    t->r = (w != NULL) ? w->renderer : g_window->renderer;

    SDL_FreeSurface(s);

    return t;

}

/* ================================================================ */

void Texture_destroy(Texture_t* t) {

    if ((t != NULL) && (*t != NULL)) {

        SDL_DestroyTexture((*t)->t);

        free(*t);

        *t = NULL;
    }

    return ;
}

/* ================================================================ */

int Texture_display(const Texture_t t, SDL_Rect* src, SDL_Rect* dst) {

    if (t == NULL) {
        return EXIT_FAILURE;
    }

    return SDL_RenderCopy(t->r, t->t, src, dst);
}

/* ================================================================ */
