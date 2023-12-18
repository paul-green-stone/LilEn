#ifndef LILEN_TEXTURE_H
#define LILEN_TEXTURE_H

#include "../LilEn.h"

/* ================================================================ */

struct texture {

    /* Texture */
    SDL_Texture* t;

    /* Renderer */
    SDL_Renderer* r;
};

/* ================================================================ */
/* ========================== INTERFACE =========================== */
/* ================================================================ */

extern Texture_t Texture_new(const char* pathname, const Window_t w);

/* ================================ */

extern void Texture_destroy(Texture_t* t);

/* ================================ */

extern int Texture_display(const Texture_t t, SDL_Rect* src, SDL_Rect* dst);

/* ================================================================ */

#endif /* LILEN_TEXTURE_H */
