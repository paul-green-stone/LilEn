#ifndef LILEN_TEXT_H
#define LILEN_TEXT_H

#include "../LilEn.h"

/* ================================================================ */

/**
 * Create a font from a file, using a specified point size.
*/
#define Font_load(file, size) (TTF_OpenFont(file, size))

/**
 * Call this when done with a font. This function will free any resources associated with it.
 * It is safe to call this function on NULL, for example on the result of a failed call to `Font_load()`.
*/
#define Font_unload(font) (TTF_CloseFont(font))

/* ================================================================ */

struct text {
    SDL_Rect position;      /* Position on the screen */

    SDL_Texture* t;         /* Texture to be displayed */
};

/* ================================================================ */

/**
 * Create a new instance of a `Text_t` type.
*/
extern Text_t Text_new(const char* value, const TTF_Font* font);

/**
 * Destroy a text of type `Text_t`. Free any resources associated with it.
*/
extern void Text_destroy(Text_t* text);

/**
 * 
*/
extern int Text_update(const Text_t text, const char* value, const TTF_Font* font);

/**
 * 
*/
extern int Text_display(const Text_t text, const Window_t w);

/* ================================================================ */

#endif /* LILEN_TEXT_H */
