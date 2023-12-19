#include "../LilEn.h"

/* ================================================================ */

Button_t Button_new(int x, int y, int w, int h) {

    Button_t button = NULL;

    if ((w < 0) || (h < 0)) {
        
        /* Set an error code */
        return button;
    }

    if ((button = (Button_t) calloc(1, sizeof(Button))) == NULL) {

        return button;
    }

    button->dimensions = (SDL_Rect) {x, y, w, h};

    return button;
}

/* ================================================================ */

void Button_destroy(Button_t* button) {

    if ((button == NULL) || (*button == NULL)) {
        return ;
    }

    Text_destroy(&(*button)->label);

    Texture_destroy(&(*button)->texture);

    free(*button);

    *button = NULL;

    return ;
}

/* ================================================================ */

int Button_display(const Button_t b, const Window_t w) {

    if (b == NULL) {
        return EXIT_FAILURE;
    }

    if ((w == NULL) && (g_window == NULL)) {
        return EXIT_FAILURE;
    }

    (b->is_solid) ? LilEn_draw_rect(w, &b->dimensions) : LilEn_outline_rect(w, &b->dimensions);

    return EXIT_SUCCESS;
}

/* ================================================================ */

void Button_check(const Button_t btn, SDL_MouseButtonEvent* b, const SDL_Point* p, void* callback_argc) {

    if (btn == NULL) {
        return ;
    }

    if ((btn->on_hover != NULL) && (LilEn_is_inside(&btn->dimensions, p)) && (b->button != SDL_BUTTON_LEFT)) {
        btn->on_hover(callback_argc);
    }

    if ((btn->on_click != NULL) && (LilEn_is_inside(&btn->dimensions, p)) && (b->button == SDL_BUTTON_LEFT)) {
        btn->on_click(callback_argc);
    }

    return ;
}

/* ================================================================ */
