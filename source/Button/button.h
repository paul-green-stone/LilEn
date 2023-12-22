#ifndef LILEN_BUTTON_H
#define LILEN_BUTTON_H

#include "../LilEn.h"

/* ================================================================ */

struct button {

    SDL_Rect dimensions;

    Text_t label;

    Texture_t texture;

    void (*on_click)(void* args);

    int is_solid;

    int is_hover;
};

/* ================================================================ */
/* ========================== INTERFACE =========================== */
/* ================================================================ */

extern Button_t Button_new(int x, int y, int w, int h);

/* ================================ */

extern Button_t Button_new_Text(int x, int y, int w, int h, const char* label, TTF_Font* font);

/* ================================ */

extern void Button_destroy(Button_t* button);

/* ================================ */

extern int Button_display(const Button_t b, const Window_t w);

/* ================================ */

extern void Button_click(const Button_t btn, const SDL_Point* p, void* callback_args);

/* ================================================================ */

#endif /* LILEN_BUTTON_H */
