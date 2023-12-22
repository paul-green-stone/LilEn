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

Button_t Button_new_Text(int x, int y, int w, int h, const char* label, TTF_Font* font) {

    Button_t button = NULL;

    if ((w < 0) || (h < 0)) {
        
        /* Set an error code */
        return button;
    }

    if ((button = (Button_t) calloc(1, sizeof(Button))) == NULL) {

        return button;
    }

    button->dimensions.x = x;
    button->dimensions.y = y;

    if ((button->label = Text_new(label, font)) == NULL) {
        Button_destroy(&button);
    }

    if (button->label->position.w < w) {
        button->label->position.x = (w / 2 - button->label->position.w / 2) + button->dimensions.x;

        button->dimensions.w = w;
    }
    else if (button->label->position.w >= w) {
        button->label->position.x = button->dimensions.x;

        button->dimensions.w = button->label->position.w;
    }

    if (button->label->position.h < h) {
        button->label->position.y = (h / 2 - button->label->position.h / 2) + button->dimensions.y;

        button->dimensions.h = h;
    }
    else if (button->label->position.h >= h) {
        button->label->position.y = button->dimensions.y;

        button->dimensions.h = button->label->position.h;
    }

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

    if (b->label != NULL) {
        Text_display(b->label, w);
    }

    (b->is_solid) ? LilEn_draw_rect(w, &b->dimensions) : LilEn_outline_rect(w, &b->dimensions);

    return EXIT_SUCCESS;
}

/* ================================================================ */

void Button_click(const Button_t btn, const SDL_Point* p, void* callback_args) {

    if (btn == NULL) {
        return ;
    }

    btn->is_hover = LilEn_is_inside(&btn->dimensions, p);

    if ((btn->on_click != NULL) && (btn->is_hover)) {
        btn->on_click(callback_args);
    }

    return ;
}

/* ================================================================ */
