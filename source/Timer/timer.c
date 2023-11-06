#include "../LilEn.h"

/* ================================================================ */

Timer_t Timer_new(void) {

    Timer_t t = NULL;

    if ((t = (Timer_t) calloc(1, sizeof(Timer))) == NULL) {
        return t;
    }

    t->pt = SDL_GetPerformanceCounter();

    return t;
}

/* ================================================================ */

extern void Timer_destroy(Timer_t* t) {

    if ((t == NULL) || (t != NULL)) {
        return ;
    }

    free(*t);

    *t = NULL;

    return ;
}

/* ================================================================ */

int Timer_set(const Timer_t t, float v) {

    if (t == NULL) {
        return EXIT_FAILURE;
    }

    if (v <= 0) {

        /* This one is causing an error */

        return EXIT_FAILURE;
    }

    t->time = v;

    return EXIT_SUCCESS;
}

/* ================================================================ */

int Timer_is_ready(const Timer_t t) {
    return (t != NULL) ? t->acc >= t->time : 0;
}

/* ================================================================ */

int Timer_reset(const Timer_t t) {

    if (t == NULL) {
        return EXIT_FAILURE;
    }

    t->acc = 0;

    return EXIT_SUCCESS;
}

/* ================================================================ */

void Timer_tick(const Timer_t t) {

    /* Current frame start */
    uint64_t current_ticks = 0;

    uint64_t delta = 0;

    if (t == NULL) {

        fprintf(stderr, "%s error: %s\n", __func__, "provided timer is NULL");

        return ;
    }

    /* ======== */

    current_ticks = SDL_GetPerformanceCounter();

    /* How many ticks have passed since the last frame */
    delta = current_ticks - t->pt;

    t->pt = current_ticks;

    /* Compute how many SECONDS have passed since the previous frame */
    t->d = (float) delta / (float) SDL_GetPerformanceFrequency();

    t->acc += t->d;

    /* ======== */

    return ;
}
