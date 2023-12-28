#include "../LilEn.h"

/* ================================================================ */

struct state {

    /* It tells whether a mouse cursor is within the boundaries of the button or not */
    int is_hover;

    /* A mouse button that is associated with the current button */
    int mb;

    /* To handle an `ON_MOUSE_LEAVE` event, we need to monitor the mouse cursor movements and detect when it leaves the button. When the mouse cursor enters the button, we set the variable to indicate that the button is ready to initiate an `ON_MOUSE_LEAVE` callback */
    int is_left;

    /* A button callback function that is invoked when the button is clicked */
    void (*on_click)(void* args);

    /* A button callback function that is invoked when the mouse cursor enters the button */
    void (*on_mouse_enter)(void* args);

    /* A button callback function that is invoked when the mouse cursor leaves the button */
    void (*on_mouse_leave)(void* args);
};

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

    if ((button->state = (struct state*) calloc(1, sizeof(struct state))) == NULL) {
        Button_destroy(&button);
    }

    button->dimensions = (SDL_Rect) {x, y, w, h};

    printf("%d, %d, %d, %d\n", button->dimensions.x, button->dimensions.y, button->dimensions.w, button->dimensions.h);

    return button;
}

/* ================================================================ */

Button_t Button_new_Text(int x, int y, int w, int h, const char* label, TTF_Font* font) {

    Button_t button = NULL;

    if ((button = Button_new(x, y, w, h)) == NULL) {
        return button;
    }

    if ((button->label = Text_new(label, font)) == NULL) {
        Button_destroy(&button);
    }

    if ((button->label != NULL)) {
        strncpy(button->text, label, BUTTON_TEXT_SIZE - 1);

        button->text[strlen(button->text)] = '\0';
    }

    /* Center the text in the button if its width less than the button's width */
    if (button->label->position.w < w) {
        button->label->position.x = (w / 2 - button->label->position.w / 2) + button->dimensions.x;

        button->dimensions.w = w;
    }
    /* Make the button's width equal to the text's width to fit it inside */
    else if (button->label->position.w >= w) {
        button->label->position.x = button->dimensions.x;

        button->dimensions.w = button->label->position.w;
    }

    /* Center the text in the button if its height less than the button's height */
    if (button->label->position.h < h) {
        button->label->position.y = (h / 2 - button->label->position.h / 2) + button->dimensions.y;

        button->dimensions.h = h;
    }
    /* Make the button's height equal to the text's height to fit it inside */
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

    free((void*) (*button)->state);

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

    if (b->is_solid) {
        LilEn_draw_rect(w, &b->dimensions);
    }

    if (b->is_border) {
        LilEn_outline_rect(w, &b->dimensions);
    }

    if (b->label != NULL) {
        Text_display(b->label, w);
    }

    return EXIT_SUCCESS;
}

/* ================================================================ */

void Button_hover(const Button_t btn, const SDL_Point* p, void* callback_args) {

    if (btn == NULL) {
        return ;
    }

    btn->state->is_hover = LilEn_is_inside(&btn->dimensions, p);

    if ((btn->state->on_mouse_enter != NULL) && (btn->state->is_hover) && (!btn->state->is_left)) {
        btn->state->on_mouse_enter(callback_args);

        btn->state->is_left = !btn->state->is_left;
    }

    if ((btn->state->on_mouse_leave != NULL) && (!btn->state->is_hover) && (btn->state->is_left)) {
        btn->state->on_mouse_leave(callback_args);

        btn->state->is_left = !btn->state->is_left;
    }

    return ;
}

/* ================================================================ */

int Button_add_callback(const Button_t btn, int event, void (*callback)(void*)) {

    int exit_code = EXIT_SUCCESS;

    if (btn == NULL) {
        return EXIT_FAILURE;
    }

    switch (event) {
        
        case ON_CLICK:

            btn->state->on_click = callback;

            break ;

        /* ======== */

        case ON_MOUSE_ENTER:

            btn->state->on_mouse_enter = callback;

            break ;

        /* ======== */

        case ON_MOUSE_LEAVE:

            btn->state->on_mouse_leave = callback;

            break ;

        /* ======== */

        default:

            exit_code = EXIT_FAILURE;

            break ;
    }

    return exit_code;
}

/* ================================================================ */

void Button_click(const Button_t btn, const SDL_Point* p, SDL_MouseButtonEvent mb, void* callback_args) {

    if ((btn->state->is_hover = LilEn_is_inside(&btn->dimensions, p)) && (mb.button == btn->state->mb)) {
        btn->state->on_click(callback_args);
    }

    return ;
}

/* ================================================================ */

int Button_bind_mb(const Button_t btn, int sdl_mouse_button) {
    
    if (btn == NULL) {
        return EXIT_FAILURE;
    }

    btn->state->mb = sdl_mouse_button;

    return EXIT_SUCCESS;
}

/* ================================================================ */

#undef BUTTON_TEXT_SIZE
