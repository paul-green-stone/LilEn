#ifndef LILEN_BUTTON_H
#define LILEN_BUTTON_H

#include "../LilEn.h"

/* ================================================================ */

struct button {

    SDL_Rect dimensions;

    Text_t label;

    Texture_t texture;

    void (*on_click)(void*);
    void (*on_hover)(void*);

    int is_solid;
};

/* ================================================================ */
/* ========================== INTERFACE =========================== */
/* ================================================================ */

extern Button_t Button_new(int x, int y, int w, int h);

/* ================================ */

extern void Button_destroy(Button_t* button);

/* ================================ */

extern int Button_display(const Button_t b, const Window_t w);

/* ================================ */

extern void Button_check(const Button_t btn, SDL_MouseButtonEvent* b, const SDL_Point* p, void* callback_argc);

/* ================================================================ */

#endif /* LILEN_BUTTON_H */
