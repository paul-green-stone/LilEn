#ifndef LILEN_BUTTON_H
#define LILEN_BUTTON_H

#include "../LilEn.h"

#define BUTTON_TEXT_SIZE 16

/* ================================================================ */

struct button {

    /* Button's position on the screen, its width and height */
    SDL_Rect dimensions;

    /* The text a button contains  */
    Text_t label;

    char text[BUTTON_TEXT_SIZE];

    Texture_t texture;

    int is_solid;

    int is_border;

    /* A pointer to an incomplete data type that stores button information, such as its callbacks. A user can only assign a callback function to the button via defined functions */
    struct state* state;
};

/* Button callbacks */
enum BTN_CLBS {
    /* Happens when the button is clicked */
    ON_CLICK = 0,

    /* Happens when the mouse cursor enters the button */
    ON_MOUSE_ENTER = 1,

    /* Happens when the mouse cursor leaves the button */
    ON_MOUSE_LEAVE = 2,
};

/* ================================================================ */
/* ========================== INTERFACE =========================== */
/* ================================================================ */

/**
 * Create a new instance of a `Button_t` type. Returns `Button_t` on success or `NULL` on failure; call `LilEn_print_error` for more information.
*/
extern Button_t Button_new(int x, int y, int w, int h);

/* ================================ */

/**
 * Create a new instance of a `Button_t` type with the specfied label. Returns `Button_t` on success or `NULL` on failure; call `LilEn_print_error` for more information.
*/
extern Button_t Button_new_Text(int x, int y, int w, int h, const char* label, TTF_Font* font);

/* ================================ */

/**
 * Destroy the button and free associated resources. If the operation is successful, the button will be `NULL`.
*/
extern void Button_destroy(Button_t* button);

/* ================================ */

/**
 * Display a button on the screen. Use `g_window` if `w` is NULL.
*/
extern int Button_display(const Button_t b, const Window_t w);

/* ================================ */

/**
 * Handle `ON_MOUSE_ENTER` and `ON_MOUSE_LEAVE` events.
*/
extern void Button_hover(const Button_t btn, const SDL_Point* p, void* callback_args);

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
 * Bind a "physical" mouse button to the "virtual" button. Returns `EXIT_SUCCESS` on success or `EXIT_FAILURE` on failure; call `LilEn_print_error` for more information.
*/
extern int Button_bind_mb(const Button_t btn, int sdl_mouse_button);

/* ================================================================ */

#endif /* LILEN_BUTTON_H */
