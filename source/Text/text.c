#include "../../LilEn.h"

/* ================================================================ */

Text_t Text_new(const char* value, const TTF_Font* font) {

    Text_t text = NULL;

    if (value == NULL) {
        return NULL;
    }

    if (font == NULL) {
        return NULL;
    }

    if ((text = (Text_t) calloc(1, sizeof(struct text))) == NULL) {
        return NULL;
    }

    if (Text_update(text, value, font) == EXIT_FAILURE) {
        Text_destroy(&text);
    }

    return text;
}

/* ================================================================ */

int Text_update(const Text_t text, const char* value, const TTF_Font* font) {

    SDL_Surface* s = NULL;
    SDL_Texture* t = NULL;

    if (text == NULL) {
        return EXIT_FAILURE;
    }

    if (value == NULL) {
        return EXIT_FAILURE;
    }

    if ((s = TTF_RenderText_Solid((TTF_Font*) font, value, *g_color)) == NULL) {
        goto ERROR;
    }

    if ((t = SDL_CreateTextureFromSurface(g_window->renderer, s)) == NULL) {
        goto ERROR;
    }

    if (text->t != NULL) {
        SDL_DestroyTexture(text->t);
    }

    text->t = t;

    SDL_QueryTexture(t, NULL, NULL, &text->position.w, &text->position.h);
    SDL_FreeSurface(s);

    return EXIT_SUCCESS;

    { ERROR:
        SDL_FreeSurface(s);

        return EXIT_FAILURE;
    }
}

/* ================================================================ */

void Text_destroy(Text_t* text) {

    if ((text == NULL) || (*text == NULL)) {
        return ;
    }

    SDL_DestroyTexture((*text)->t);
    free(*text);

    *text = NULL;

    return ;
}

/* ================================================================ */

int Text_display(const Text_t text, const Window_t w) {

    if (text == NULL) {
        return EXIT_FAILURE;
    }

    if ((w == NULL) && (g_window == NULL)) {
        return EXIT_FAILURE;
    }

    return (SDL_RenderCopy((w == NULL) ? g_window->renderer : w->renderer, text->t, NULL, &text->position));
}
