#ifndef LILEN_BUTTON_H
#define LILEN_BUTTON_H

#include "../LilEn.h"

/* ================================================================ */

struct button {

    SDL_Rect dimensions;

    Text_t label;

    Texture_t texture;

    int is_solid;

    /* A pointer to an incomplete data type that stores button information, such as its callbacks. A user can only assign a callback function to the button via defined functions */
    struct state* state;
};

enum BTN_CLBS {
    ON_CLICK = 0,
    ON_MOUSE_ENTER = 1,
    ON_MOUSE_LEAVE = 2,
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

/**
 * Handle `ON_MOUSE_ENTER` and `ON_MOUSE_LEAVE` events.
*/
extern void Button_hover(const Button_t btn, const SDL_Point* p, SDL_MouseButtonEvent mb, void* callback_args);

/* ================================ */

/**
 * Add a callback function to the given button. The `event` argument, one of `ON_CLICK`, `ON_MOUSE_ENTER`, or `ON_MOUSE_LEAVE`, specifies an event that will trigger the callback. Returns `EXIT_SUCCESS` on success or `EXIT_FAILURE` on failure; call `LilEn_print_error` for more information.
*/
extern int Button_add_callback(const Button_t btn, int event, void (*callback)(void*));

/* ================================ */

/**
 * Handle "the button has been clicked", `ON_CLICK` event.
*/
extern void Button_click(const Button_t btn, const SDL_Point* p, SDL_MouseButtonEvent mb, void* callback_args);

/* ================================ */

/**
 * 
*/
extern int Button_bind_mb(const Button_t btn, int sdl_mouse_button);

/* ================================================================ */


#endif /* LILEN_BUTTON_H */
